#include <iostream>
#include <WS2tcpip.h>
#include <string>

#pragma comment (lib, "ws2_32.lib")

#define BUFFER_SIZE 4096 

void main()
{
	// Initialize winsock

	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsOk = WSAStartup(ver, &wsData);
	if (wsOk != 0)
	{
		std::cerr << "Can't initialize winsock!" << std::endl;
		return;
	}

	// Create a socket

	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
	{
		std::cerr << "Can't create a socket" << std::endl;
		return;
	}

	// Bind the IP address and port to a socket

	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(listening, (sockaddr*)&hint, sizeof(hint));

	// Tell Winsock the socket is for listening
	listen(listening, SOMAXCONN);

	fd_set master;
	FD_ZERO(&master);

	FD_SET(listening, &master);

	while (true)
	{
		fd_set copy = master;

		int socketCount = select(0, &copy, nullptr, nullptr, nullptr);

		for (int i = 0; i < socketCount; i++)
		{
			SOCKET sock = copy.fd_array[i];
			if (sock == listening)
			{
				// Accept a new connection
				sockaddr_in clientAddr;
				int clientSize = sizeof(clientAddr);
				SOCKET clientSocket = accept(listening, (sockaddr*)&clientAddr, &clientSize);

				// Add the new connection to the list of connected clients
				FD_SET(clientSocket, &master);

				// Send a welcome message to the connected client
				//std::string welcomeMsg = "Welcome to the server!";
				//send(clientSocket, welcomeMsg.c_str(), welcomeMsg.size() + 1, 0);

				// Broadcast that client connected
				std::cout << "Client #" << i << " connected." << std::endl;
			}
			else
			{
				char buf[BUFFER_SIZE];
				ZeroMemory(buf, BUFFER_SIZE);

				// Receive message
				int bytesIn = recv(sock, buf, BUFFER_SIZE, 0);
				if (bytesIn <= 0)
				{
					// Drop the client
					closesocket(sock);
					FD_CLR(sock, &master);
				}
				else
				{
					std::cout << std::string(buf, 0, bytesIn) << std::endl;
					//send(sock, )
					//for (int i = 0; i < master.fd_count; i++)
					//{
					//	SOCKET outSock = master.fd_array[i];
					//	if (outSock != listening && outSock != sock)
					//	{
					//		send(outSock, buf, bytesIn, 0);
					//	}
					//}
				}
				
			}

		}
	}

	// Cleanup winsock
	WSACleanup();
}