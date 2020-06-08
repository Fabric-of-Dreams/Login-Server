#include "MultiClientListener.h"
#include <string>

// Handler for client connections
void MultiClientListener::onClientConnected(int clientSocket)
{
	std::cout << "Client with socket #" << clientSocket << " connected." << std::endl;
}

// Handler for client disconnections
void MultiClientListener::onClientDisconnected(int clientSocket)
{
	std::cout << "Client with socket #" << clientSocket << " disconnected." << std::endl;
}

void MultiClientListener::onMessageReceived(int sock, const char* msg, int bytesIn)
{
	std::cout << std::string(msg, 0, bytesIn) << std::endl;
	sendToClient(sock, "I don't check your password");
}