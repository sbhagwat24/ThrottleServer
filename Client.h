#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "NetworkHost.h"
#include <string>

class Client : protected NetworkHost
{
	const std::string m_serverName;

public:
	Client(const std::string& server, int port)
		: NetworkHost(port), m_serverName(server) {}

	Client(const std::string& server, int port, int domain)
		: NetworkHost(port, domain), m_serverName(server) {}

	Client(const std::string& server, int port, int domain, int type)
		: NetworkHost(port, domain, type), m_serverName(server) {}

	/* Connect to server and send the request. Read server's reply*/
	void run(const std::string& request);
};

#endif
