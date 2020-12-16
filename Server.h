#ifndef _SERVER_H_
#define _SERVER_H_

#include "NetworkHost.h"
#include "Config.h"
#include <string>
#include <memory>

const int SERVER_THREADS = 100;
const int BACKLOG_QUEUE_SIZE = 10;

class Server : protected NetworkHost
{
public:
        Server(int port)
		: NetworkHost(port), m_threads(SERVER_THREADS), m_backlog(BACKLOG_QUEUE_SIZE) {}

        Server(int port, int domain)
		: NetworkHost(port, domain), m_threads(SERVER_THREADS), m_backlog(BACKLOG_QUEUE_SIZE) {}

        Server(int port, int domain, int type)
		: NetworkHost(port, domain, type), m_threads(SERVER_THREADS), m_backlog(BACKLOG_QUEUE_SIZE) {}

	/* 
 	* Start the server and wait for requests
 	* Accept/Deny requests based on throttling configuration for each user specified in the user conf file
 	* Run threads in parallel to cater to multiple users
 	*/ 
	void run();

	/*
 	* Validates user w.r.t config file
 	* Validates if user has valid tokens for the current request
 	*/
	bool validateRequest(const std::string &request) const;

	/*
 	* Read configuration file for user throttling information
 	*/ 
	bool configure(const std::string &file);

private:
	const int m_threads;  //total threads

	const int m_backlog;  //maximum number of queued connections requests

	std::unique_ptr<Config> m_conf;  //user throttling configuration
};

#endif
