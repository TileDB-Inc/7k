// Teledyne Marine

// Use and Disclosure of Data
//
// EU Uncontrolled Technology: Information contained herein is uncontrolled
// under the E.U. Regulation (EC) No 428/2009.
// However, export, reexport or diversion contrary to law is prohibited.


#include "stdafx.h"
#include "TcpSocket7k.h"

#include <cassert>
#include <cstring>

#include "7k.h"


namespace
{
	const int TCP_PORT_7K = 7000;
	const u32 MAX_PACKET_SIZE = 60000;
}


TcpSocket7k::TcpSocket7k()
	: m_socket()
	, m_nextTransmissionId(0)
{
}


bool TcpSocket7k::Create()
{
	return m_socket.Create(NetworkSocket::TYPE_TCP);
}


bool TcpSocket7k::Connect(const char* host)
{
	return m_socket.Connect(host, TCP_PORT_7K);
}


void TcpSocket7k::Close()
{
	m_socket.Close();
}


bool TcpSocket7k::SendRecord(u32 deviceId, u16 enumerator, u32 recordType,
		const void* pData, size_t dataSize)
{
	u32 recordSize = sizeof(RECORD_FRAME) + (u32) dataSize + CHECKSUM_SIZE;
	u32 totalPackets = 1;
	u32 packetSize = sizeof(NETWORK_FRAME) + recordSize;

	// Splitting large records into multiple packets is not implemented here
	// because it is not needed for sending small commands
	assert(packetSize <= MAX_PACKET_SIZE);

	std::vector<u8> buffer(packetSize);
	u8* ptr = &buffer[0];

	NETWORK_FRAME nf = {};
	nf.version = PROTOCOL_VERSION;
	nf.offset = sizeof(NETWORK_FRAME);
	nf.total_packets = totalPackets;
	nf.total_records = 1;
	nf.transmission_identifier = m_nextTransmissionId++;
	nf.packet_size = packetSize;
	nf.total_size = recordSize;
	nf.sequence_number = 0;
	nf.destination_device_identifier = 0;
	nf.destination_system_enumerator = 0;
	nf.source_system_enumerator = 0;
	nf.source_device_identifier = 0;
	std::memcpy(ptr, &nf, sizeof(nf));
	ptr += sizeof(nf);

	RECORD_FRAME rf = {};
	rf.version = PROTOCOL_VERSION;
	rf.offset = sizeof(RECORD_FRAME) - SYNC_PATTERN_OFFSET;
	rf.sync_pattern = SYNC_PATTERN;
	rf.size = recordSize;
	rf.offset_optional = 0;
	rf.identifier_optional = 0;
	rf.time_stamp = TIME_7K();  // empty time stamp
	rf.records_version = RECORDS_VERSION;
	rf.record_type = recordType;
	rf.device_identifier = deviceId;
	rf.reserved1 = 0;
	rf.system_enumerator = enumerator;
	rf.record_count = 0;
	rf.flags = 0;  // no checksum
	rf.reserved2 = 0;
	rf.reserved3 = 0;
	rf.total_records = 0;
	rf.fragment_number = 0;
	std::memcpy(ptr, &rf, sizeof(rf));
	ptr += sizeof(rf);

	std::memcpy(ptr, pData, dataSize);
	ptr += dataSize;

	u32 checksum = 0;
	std::memcpy(ptr, &checksum, sizeof(checksum));

	ssize_t sentSize = m_socket.Send(&buffer[0], packetSize);
	return sentSize == (ssize_t) packetSize;
}


bool TcpSocket7k::ReceiveRecord(std::vector<u8>& recordData)
{
	NETWORK_FRAME nf;
	if (!ReceiveExact(&nf, sizeof(nf)))
		return false;

	if (nf.version != PROTOCOL_VERSION)
		return false;

	u32 totalPackets = nf.total_packets;
	u16 transmissionId = nf.transmission_identifier;
	u32 totalSize = nf.total_size;

	recordData.resize(totalSize);
	u8* pRecordData = !recordData.empty() ? &recordData[0] : 0;

	// Combine multiple packets into one large record
	size_t readSize = 0;
	for (u32 sequenceNo = 0; sequenceNo < totalPackets; ++sequenceNo)
	{
		if (sequenceNo > 0)
		{
			if (!ReceiveExact(&nf, sizeof(nf)))
				return false;

			if (nf.version != PROTOCOL_VERSION
				|| nf.total_packets != totalPackets
				|| nf.transmission_identifier != transmissionId
				|| nf.total_size != totalSize)
			{
				return false;
			}
		}

		if (nf.sequence_number != sequenceNo || nf.offset != sizeof(nf))
			return false;

		size_t payloadSize = nf.packet_size - nf.offset;
		if (payloadSize > totalSize - readSize)
			return false;

		if (!ReceiveExact(pRecordData + readSize, payloadSize))
			return false;

		readSize += payloadSize;
	}

	if (readSize != totalSize)
		return false;

	return true;
}


bool TcpSocket7k::ReceiveExact(void* pBuffer, size_t size)
{
	char* pInBuf = static_cast<char*>(pBuffer);
	size_t toDo = size;

	while (toDo > 0)
	{
		ssize_t done = m_socket.Receive(pInBuf, toDo);
		if (done <= 0)
			return false;

		pInBuf += done;
		toDo -= (size_t) done;
	}

	return true;
}


bool GetFrame(const std::vector<u8>& recordData, RECORD_FRAME& rf)
{
	if (recordData.size() < sizeof(rf))
		return false;
	std::memcpy(&rf, &recordData[0], sizeof(rf));

	if (rf.sync_pattern != SYNC_PATTERN)
		return false;

	return true;
}


const u8* GetDataPtr(const std::vector<u8>& recordData, size_t& dataSize)
{
	RECORD_FRAME rf = {};
	if (!GetFrame(recordData, rf))
		return 0;

	u16 dataOffset = rf.offset;
	u32 optionalOffset = rf.offset_optional;
	size_t recordSize = rf.size;
	if (recordData.size() < recordSize)
		return 0;

	size_t frameSize = SYNC_PATTERN_OFFSET + dataOffset;
	if (frameSize < sizeof(RECORD_FRAME))
		return 0;

	size_t optionalSize = 0;
	if (optionalOffset)
	{
		if (recordSize < optionalOffset - CHECKSUM_SIZE)
			return 0;
		optionalSize = recordSize - optionalOffset - CHECKSUM_SIZE;
	}

	if (recordSize < frameSize + optionalSize + CHECKSUM_SIZE)
		return 0;
	dataSize = recordSize - frameSize - optionalSize - CHECKSUM_SIZE;

	return &recordData[frameSize];
}
