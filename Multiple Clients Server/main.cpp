#include "WebServer.h"

int main()
{
	WebServer webServer("127.0.0.1", 8080);
	if (webServer.init() != 0)
		return -1;

	webServer.run();
}