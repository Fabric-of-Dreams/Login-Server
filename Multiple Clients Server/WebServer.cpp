#include "WebServer.h"

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <iterator>

void WebServer::onMessageReceived(int clientSocket, const char* msg, int bytesIn)
{
	// GET /index.html HTTP/1.1
	// Parse out the document requested
	std::istringstream iss(msg);
	// Makes strings separated by spaces
	std::vector<std::string> parsed((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());

	std::string content = "<h1>404 Not Found</h1>";
	std::string htmlFile = "/index.html";
	int errorCode = 404;

	// GET, name of the document (e.g. /index.html), HTTP/1.1
	if (parsed.size() >= 3 && parsed[0] == "GET")
	{
		if (parsed[1] == "/")
		{
			htmlFile = "/index.html";
		}
		else
		{
			htmlFile = parsed[1];
		}
	}

	// Open the document in the local file system
	std::ifstream f(".\\wwwroot" + htmlFile);
	if (f.good())
	{
		std::string str((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
		content = str;
		errorCode = 200;
	}

	f.close();


	// Write the document to the client
	std::ostringstream oss;
	oss << "HTTP/1.1 " << errorCode << " OK\r\n";
	oss << "Cashe-Control: no-cashe, private\r\n";
	oss << "Content-Type: text/html\r\n";
	oss << "Content-Length: " << content.size() << "\r\n";
	oss << "\r\n";
	oss << content;

	std::string output = oss.str();
	int size = output.size() + 1;

	send(clientSocket, output.c_str(), size, 0);

}

void WebServer::onClientConnected(int clientSocket)
{

}

void WebServer::onClientDisconnected(int clientSocket)
{

}
