// Teledyne Marine

// Use and Disclosure of Data
//
// EU Uncontrolled Technology: Information contained herein is uncontrolled
// under the E.U. Regulation (EC) No 428/2009.
// However, export, reexport or diversion contrary to law is prohibited.


#ifndef NETWORK_SOCKET_H
#define NETWORK_SOCKET_H


#pragma once


#ifdef _WIN32
#include <winsock2.h>
typedef SSIZE_T ssize_t;
#else
#include <sys/types.h>
typedef int SOCKET;
#endif


/*****************************************************************************
 * NetworkSocket is a class for Windows/BSD networking sockets.
 *
 ****************************************************************************/
class NetworkSocket
{
	NetworkSocket(const NetworkSocket&);
	NetworkSocket& operator=(const NetworkSocket&);

public:
	enum Type { TYPE_TCP, TYPE_UDP };
	enum How { SHUTDOWN_RECEIVES, SHUTDOWN_SENDS, SHUTDOWN_BOTH };

	static bool Init();
	static void Exit();

	NetworkSocket();
	~NetworkSocket();

	bool Create(Type type, int port = 0);
	bool ShutDown(How how = SHUTDOWN_SENDS);
	void Close();

	bool Connect(const char* host, int port);

	bool Listen();
	bool Accept(NetworkSocket& connection);

	ssize_t Receive(void* pBuffer, size_t size);
	ssize_t Send(const void* pBuffer, size_t size);

private:
	SOCKET m_hSocket;
};


#endif  // NETWORK_SOCKET_H
