#pragma once
#include "TCPListener.h"

class MultiClientListener : public TCPListener
{
public:

	MultiClientListener(const char* ipAddress, int port) :
		TCPListener(ipAddress, port)
	{

	}

protected:

	// Handler for client connections
	virtual void onClientConnected(int clientSocket);

	// Handler for client disconnections
	virtual void onClientDisconnected(int clientSocket);

	virtual void onMessageReceived(int sock, const char* msg, int bytesIn);
};

