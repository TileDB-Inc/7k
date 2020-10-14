// Teledyne Marine

// Use and Disclosure of Data
//
// EU Uncontrolled Technology: Information contained herein is uncontrolled
// under the E.U. Regulation (EC) No 428/2009.
// However, export, reexport or diversion contrary to law is prohibited.


#include "stdafx.h"
#include "Example7k.h"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>


namespace
{
	const char NAME_START[] = "<Name";
	const char DEVID_START[] = "deviceid=\"";
	const char ENUM_START[] = "enumerator=\"";

#pragma pack(push, 1)
	struct R7500_1050
	{
		R7500 r7500;
		u32 record_type;
	};

	struct R7500_1051
	{
		R7500 r7500;
		u32 record_count;
		u32 record_types[2];
	};
#pragma pack(pop)
}


// The example connects to the sonar,
// request the XML configuration record (7001),
// subscribes to the raw detections record (7027) and image data (7011),
// and prints out the last detection and center pixel of each ping

void Example7k::Run(const char* host)
{
	if (!ConnectToCenter(host))
		return;

	RequestConfig();
	ReceiveLoop();
}


bool Example7k::ConnectToCenter(const char* host)
{
	return m_socket.Create() && m_socket.Connect(host);
}


void Example7k::RequestConfig()
{
	R7500_1050 r7500_1050 = {};
	r7500_1050.r7500.rc_id = 1050;  // Single Record Request
	r7500_1050.record_type = 7001;  // Configuration

	m_socket.SendRecord(7000, 0, 7500, &r7500_1050, sizeof(r7500_1050));
}


bool Example7k::ReceiveLoop()
{
	std::vector<u8> recordData;
	while (m_socket.ReceiveRecord(recordData))
	{
		RECORD_FRAME rf = {};
		if (!GetFrame(recordData, rf))
			break;

		size_t dataSize = 0;
		const u8* pData = GetDataPtr(recordData, dataSize);

		switch (rf.record_type)
		{
		case 7001:
			HandleConfig(pData, dataSize);
			break;

		case 7011:
			HandleImage(pData, dataSize);
			break;

		case 7027:
			HandleDetections(pData, dataSize);
			break;
		}
	}

	return true;
}


// Get device identifier and enumerator from the XML configuration,
// and subscribe to the raw detections (7027) record for each system
bool Example7k::HandleConfig(const u8* pData, size_t dataSize)
{
	size_t idx = 0;

	R7001 r7001;
	if (idx + sizeof(r7001) > dataSize)
		return false;
	std::memcpy(&r7001, pData + idx, sizeof(r7001));
	idx += sizeof(R7001);

	for (u32 i = 0; i < r7001.systems; ++i)
	{
		R7001MODULEINFO r7001Info;
		if (idx + sizeof(r7001Info) > dataSize)
			return false;
		std::memcpy(&r7001Info, pData + idx, sizeof(r7001Info));
		idx += sizeof(r7001Info);

		size_t infoLen = r7001Info.info_length;

		if (idx + infoLen > dataSize)
			return false;
		const char* pInfo = reinterpret_cast<const char*>(pData + idx);
		idx += infoLen;

		if (infoLen == 0 || pInfo[infoLen - 1] != '\0')
			return false;

		// Get device id and enum from XML
		const char* pName = std::strstr(pInfo, NAME_START);
		if (!pName)
			continue;

		const char* pId = std::strstr(pName, DEVID_START);
		if (!pId)
			continue;
		u32 deviceId = (u32) std::atoi(pId + sizeof(DEVID_START) - 1);

		const char* pEnum = std::strstr(pName, ENUM_START);
		if (!pEnum)
			continue;
		u16 enumerator = (u16) std::atoi(pEnum + sizeof(ENUM_START) - 1);

		Subscribe(deviceId, enumerator);
	}

	return true;
}


void Example7k::Subscribe(u32 deviceId, u16 enumerator)
{
	R7500_1051 r7500_1051 = {};
	r7500_1051.r7500.rc_id = 1051;  // Record Subscription
	r7500_1051.record_count = 2;
	r7500_1051.record_types[0] = 7027;  // Raw Detections
	r7500_1051.record_types[1] = 7011;  // Image Data

	m_socket.SendRecord(deviceId, enumerator, 7500, &r7500_1051,
		sizeof(r7500_1051));
}


bool Example7k::HandleDetections(const u8* pData, size_t dataSize)
{
	size_t idx = 0;

	// The size of the 7027 header part is fixed
	R7027 r7027;
	if (idx + sizeof(r7027) > dataSize)
		return false;
	std::memcpy(&r7027, pData + idx, sizeof(r7027));
	idx += sizeof(r7027);

	// The size of the 7027 data parts is specified in the header
	// so that fields may be added in the future
	// We have to be able to deal with shorter (older) versions,
	// and longer (newer) versions
	size_t r7027DataSize = r7027.data_size;
	size_t minSize = (std::min)(sizeof(R7027Data), r7027DataSize);

	R7027Data r7027Data = {};
	for (u32 i = 0; i < r7027.detections; ++i)
	{
		if (idx + r7027DataSize > dataSize)
			return false;
		const u8* p7027Data = pData + idx;
		idx += r7027DataSize;

		std::memcpy(&r7027Data, p7027Data, minSize);
	}

	// Print last detection of each ping
	std::printf("Ping %u, beam %u, sample %f\n",
		(unsigned) r7027.ping_number,
		(unsigned) r7027Data.beam_number,
		r7027Data.detection);

	return true;
}


bool Example7k::HandleImage(const u8* pData, size_t dataSize)
{
	size_t idx = 0;

	R7011 r7011 = {};
	if (idx + sizeof(r7011) > dataSize)
		return false;
	std::memcpy(&r7011, pData + idx, sizeof(r7011));
	idx += sizeof(r7011);

	size_t imageDataSize = r7011.width * r7011.height * r7011.color_depth;
	if (idx + imageDataSize > dataSize)
		return false;
	const u8* pImageData = pData + idx;

	if (r7011.color_depth != 1)
		return false;  // not supported

	// Print value of the center pixel
	size_t beamNo = r7011.width / 2;
	size_t sampleNo = r7011.height / 2;
	u8 pixel = pImageData[beamNo + r7011.width * sampleNo];
	std::printf("Ping %u, image center pixel = %u\n",
		(unsigned) r7011.ping_number,
		(unsigned) pixel);

	return true;
}
