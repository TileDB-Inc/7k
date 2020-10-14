// Teledyne Marine

// Use and Disclosure of Data
//
// EU Uncontrolled Technology: Information contained herein is uncontrolled
// under the E.U. Regulation (EC) No 428/2009.
// However, export, reexport or diversion contrary to law is prohibited.


#ifndef TCP_SOCKET_7K_H
#define TCP_SOCKET_7K_H


#pragma once


#include <vector>

#include "7k.h"
#include "NetworkSocket.h"


struct RECORD_FRAME;


class TcpSocket7k
{
public:
	TcpSocket7k();

	bool Create();
	bool Connect(const char* host);
	void Close();

	bool SendRecord(u32 deviceId, u16 enumerator, u32 recordType,
		const void* pData, size_t dataSize);
	bool ReceiveRecord(std::vector<u8>& recordData);

private:
	bool ReceiveExact(void* pBuffer, size_t size);

private:
	NetworkSocket m_socket;
	u16 m_nextTransmissionId;
};


bool GetFrame(const std::vector<u8>& recordData, RECORD_FRAME& rf);
const u8* GetDataPtr(const std::vector<u8>& recordData, size_t& dataSize);


#endif  // TCP_SOCKET_7K_H
