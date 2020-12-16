#ifndef _NETWORK_HOST_H_
#define _NETWORK_HOST_H_

#include <sys/socket.h>

class NetworkHost 
{
protected:
	const int m_port;
	const int m_domain;	//protocol family should be AF_INET or AF_INET6
	const int m_type;	//protocol type for these two families is either SOCK_STREAM for TCP/IP or SOCK_DGRAM for UDP/IP

	NetworkHost(int port)
		: m_port(port), m_domain(AF_INET), m_type(SOCK_STREAM){}

	NetworkHost(int port, int domain)
		: m_port(port), m_domain(domain), m_type(SOCK_STREAM) {}

	NetworkHost(int port, int domain, int type)
		: m_port(port), m_domain(domain), m_type(type) {}
};

#endif
