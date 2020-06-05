#include <iostream>
#include <string>

#include "Database.h"
#include "TCPListener.h"

using namespace std;

Database db("db.txt");

void Listener_MessageReceived(TCPListener* listener, int client, string msg);

int main()
{
	TCPListener server("127.0.0.1", 54000, Listener_MessageReceived);

	if (server.Init())
	{
		server.Run();
	}
}

void Listener_MessageReceived(TCPListener* listener, int client, string msg)
{
	if (db.checkLoginPassword(msg))
	{
		cout << "Client entered wrong details." << endl;
		listener->Send(client, "Wrong username or password.");
	}
	else
	{
		cout << "Client logged in!" << endl;
		listener->Send(client, "Logged in!");
	}
}