// Teledyne Marine

// Use and Disclosure of Data
//
// EU Uncontrolled Technology: Information contained herein is uncontrolled
// under the E.U. Regulation (EC) No 428/2009.
// However, export, reexport or diversion contrary to law is prohibited.


// Includes
#include "stdafx.h"
#include "NetworkSocket.h"

#ifndef _WIN32
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#endif


// Macros
#ifndef _WIN32
#define INVALID_SOCKET -1
#endif


// Type definitions
#ifdef _WIN32
typedef int socklen_t;
#else
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct hostent* LPHOSTENT;
typedef struct in_addr* LPIN_ADDR;
#endif


// Local stuff
namespace
{
#if !defined _WIN32 && defined MSG_NOSIGNAL
	const int SEND_FLAGS = MSG_NOSIGNAL;
#else
	const int SEND_FLAGS = 0;
#endif
}


/*****************************************************************************
 * DESCRIPTION : Initialize sockets before usage.
 * ARGUMENTS   : 
 * RETURN      : True when successful, false otherwise.
 * REMARKS     : 
 *
 ****************************************************************************/
bool NetworkSocket::Init()
{
#ifdef _WIN32
	WORD wVersionRequested = MAKEWORD(2, 2);
	WSADATA wsaData = {};
	return WSAStartup(wVersionRequested, &wsaData) == 0;
#else
	return true;
#endif
}


/*****************************************************************************
 * DESCRIPTION : Exit sockets after usage.
 * ARGUMENTS   : 
 * RETURN      : 
 * REMARKS     : 
 *
 ****************************************************************************/
void NetworkSocket::Exit()
{
#ifdef _WIN32
	WSACleanup();
#endif
}


/*****************************************************************************
 * DESCRIPTION : Constructor.
 * ARGUMENTS   : 
 * RETURN      : 
 * REMARKS     : 
 *
 ****************************************************************************/
NetworkSocket::NetworkSocket()
	: m_hSocket(INVALID_SOCKET)
{
}


/*****************************************************************************
 * DESCRIPTION : Destructor.
 * ARGUMENTS   : 
 * RETURN      : 
 * REMARKS     : Closes the socket.
 *
 ****************************************************************************/
NetworkSocket::~NetworkSocket()
{
	Close();
}


/*****************************************************************************
 * DESCRIPTION : Create a socket, and bind it to a local port.
 * ARGUMENTS   : type - Socket type.
 *               port - Port number. Use 0 for any port. Default is 0.
 * RETURN      : True when successful, false otherwise.
 * REMARKS     : 
 *
 ****************************************************************************/
bool NetworkSocket::Create(Type type, int port)
{
	Close();

	int nSocketType = 0;
	switch (type)
	{
	case TYPE_TCP:
		nSocketType = SOCK_STREAM;
		break;
	case TYPE_UDP:
		nSocketType = SOCK_DGRAM;
		break;
	default:
		return false;
	}

	m_hSocket = socket(AF_INET, nSocketType, 0);
	if (m_hSocket == INVALID_SOCKET)
		return false;

	SOCKADDR_IN sockAddr = {};
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_port = htons((u_short) port);
	sockAddr.sin_addr.s_addr = INADDR_ANY;

	if (bind(m_hSocket, reinterpret_cast<SOCKADDR*>(&sockAddr),
			sizeof(sockAddr)) != 0)
	{
		return false;
	}

#if !defined _WIN32 && defined SO_NOSIGPIPE
	int val = 1;
	setsockopt(m_hSocket, SOL_SOCKET, SO_NOSIGPIPE, &val, sizeof(val));
#endif

	return true;
}


/*****************************************************************************
 * DESCRIPTION : Shut down sends, receives, or both.
 * ARGUMENTS   : how - How to shut down. Default is SHUTDOWN_SENDS.
 * RETURN      : True when successful, false otherwise.
 * REMARKS     : 
 *
 ****************************************************************************/
bool NetworkSocket::ShutDown(How how)
{
	return shutdown(m_hSocket, static_cast<int>(how)) == 0;
}


/*****************************************************************************
 * DESCRIPTION : Close the socket.
 * ARGUMENTS   : 
 * RETURN      : 
 * REMARKS     : 
 *
 ****************************************************************************/
void NetworkSocket::Close()
{
#ifdef _WIN32
	closesocket(m_hSocket);
#else
	close(m_hSocket);
#endif
	m_hSocket = INVALID_SOCKET;
}


/*****************************************************************************
 * DESCRIPTION : Connect a client socket to a server.
 * ARGUMENTS   : host - Host name or address of the server.
 *               port - Port number on the server.
 * RETURN      : True when successful, false otherwise.
 * REMARKS     : Call Create() first.
 *
 ****************************************************************************/
bool NetworkSocket::Connect(const char* host, int port)
{
	SOCKADDR_IN sockAddr = {};
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_port = htons((u_short) port);

	sockAddr.sin_addr.s_addr = inet_addr(host);
	if (sockAddr.sin_addr.s_addr == INADDR_NONE)
	{
		LPHOSTENT lphost = gethostbyname(host);
		if (!lphost)
			return false;

		sockAddr.sin_addr.s_addr = reinterpret_cast<LPIN_ADDR>(
			lphost->h_addr)->s_addr;
	}

	if (connect(m_hSocket, reinterpret_cast<SOCKADDR*>(&sockAddr),
			sizeof(sockAddr)) != 0)
	{
		return false;
	}

	return true;
}


/*****************************************************************************
 * DESCRIPTION : Configure socket as a server that listens for connections.
 * ARGUMENTS   : 
 * RETURN      : True when successful, false otherwise.
 * REMARKS     : Call Create() first.
 *
 ****************************************************************************/
bool NetworkSocket::Listen()
{
	if (listen(m_hSocket, SOMAXCONN) != 0)
		return false;

	return true;
}


/*****************************************************************************
 * DESCRIPTION : Accept a connection with a client.
 * ARGUMENTS   : connection - Socket for accepting the incoming connection.
 * RETURN      : True when successful, false otherwise.
 * REMARKS     : Call Listen() first.
 *
 ****************************************************************************/
bool NetworkSocket::Accept(NetworkSocket& connection)
{
	SOCKET hConnection = accept(m_hSocket, 0, 0);
	if (hConnection == INVALID_SOCKET)
		return false;

	connection.Close();
	connection.m_hSocket = hConnection;

	return true;
}


/*****************************************************************************
 * DESCRIPTION : Receive some data from the socket.
 * ARGUMENTS   : pBuffer - Data buffer.
 *               size    - Buffer size.
 * RETURN      : Number of bytes actually received. Zero when connection was
 *               closed. Negative when an error occurred.
 * REMARKS     : Waits until data arrives, and then returns any received data
 *               up to the buffer size.
 *
 ****************************************************************************/
ssize_t NetworkSocket::Receive(void* pBuffer, size_t size)
{
	return recv(m_hSocket, static_cast<char*>(pBuffer), size, 0);
}


/*****************************************************************************
 * DESCRIPTION : Send some data over the socket.
 * ARGUMENTS   : pBuffer - Data buffer.
 *               size    - Buffer size.
 * RETURN      : Number of bytes actually sent. Negative when an error
 *               occurred.
 * REMARKS     :
 *
 ****************************************************************************/
ssize_t NetworkSocket::Send(const void* pBuffer, size_t size)
{
	return send(m_hSocket, static_cast<const char*>(pBuffer), size,
		SEND_FLAGS);
}
