// Teledyne Marine

// Use and Disclosure of Data
//
// EU Uncontrolled Technology: Information contained herein is uncontrolled
// under the E.U. Regulation (EC) No 428/2009.
// However, export, reexport or diversion contrary to law is prohibited.


#ifndef EXAMPLE_7K_H
#define EXAMPLE_7K_H


#pragma once


#include "TcpSocket7k.h"


class Example7k
{
public:
	void Run(const char* host);

private:
	bool ConnectToCenter(const char* host);
	void RequestConfig();
	bool ReceiveLoop();
	bool HandleConfig(const u8* pData, size_t dataSize);
	void Subscribe(u32 deviceId, u16 enumerator);
	bool HandleDetections(const u8* pData, size_t dataSize);
	bool HandleImage(const u8* pData, size_t dataSize);

private:
	TcpSocket7k m_socket;
};


#endif  // EXAMPLE_7K_H
