#pragma once
#include "TCPListener.h"

class WebServer : public TCPListener
{
public:

	WebServer (const char* ipAddress, int port) :
		TCPListener(ipAddress, port)
	{

	}

protected:

	// Handler for client connections
	virtual void onClientConnected(int clientSocket);

	// Handler for client disconnections
	virtual void onClientDisconnected(int clientSocket);

	virtual void onMessageReceived(int clientSocket, const char* msg, int bytesIn);
};

