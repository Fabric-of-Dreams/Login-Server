#pragma once
#pragma comment (lib, "ws2_32.lib")

#include <WS2tcpip.h>
#include <string>

#define MAX_BUFFER_SIZE 4096

// Forward declaration
class TCPListener;

// Callback to data received
typedef void (*MessageReceivedHandler)(TCPListener* listener, int socketID, std::string msg);

class TCPListener
{
public:
	TCPListener(std::string ipAddress, int port, MessageReceivedHandler handler);
	~TCPListener();

	// Send a message to  the specified client
	void Send(int clientSocket, std::string msg);

	// Initialize winsock
	bool Init();

	// The main processing loop
	void Run();

	void Cleanup();

private:
	std::string m_ipAddress;
	int m_port;
	MessageReceivedHandler MessageReceived;

	SOCKET CreateSocket();
	SOCKET WaitForConnection(SOCKET listener);
};

