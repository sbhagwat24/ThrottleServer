#include <netinet/in.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <thread>
#include <map>
#include "User.h"
#include "Server.h"

bool Server::configure(const std::string& file)
{
	m_conf = std::unique_ptr<Config>(new Config(file));
	return m_conf->loadConfig();
}

bool Server::validateRequest(const std::string& request) const
{
	// Sample request: User1
	// Request will just have userName.
	// Verify if the user has valid tokens left
	std::map<std::string, User>::iterator it = m_conf->m_config.find(request);
	if(it != m_conf->m_config.end() )
	{
		Request req(Request::reqType::LOGIN);
		return it->second.getToken(req);
	}	
	else
	{
		return false;
	}
}

void handle_request(int sockfd, struct sockaddr_in *address, Server *s)
{
	int new_socket = 0;
	int addrlen = sizeof(address);

	if ((new_socket = accept(sockfd, (struct sockaddr *) &address, (socklen_t *) &addrlen)) < 0)
	{
		std::cerr << "Server socket accept failed!" << std::endl;
		exit(1);
	}

	char request[100] = { 0 };
	int readCnt = read(new_socket, request, sizeof(request));
	if(readCnt > 0)
	{
		if(s->validateRequest(request))
		{
			std::string response = "Allow ";
			response += request;
			int n = write(new_socket, response.c_str(), response.length());
			if (n == 0)
			{
				std::cerr << "Socket write failed";
			}
		}
		else
		{
			std::string response = "Deny ";
			response += request;
			int n = write(new_socket, response.c_str(), response.length());
			if (n == 0)
			{
				std::cerr << "Socket write failed";
			}
		}
	}
	close(new_socket);
}

void Server::run()
{
	int sockfd = 0;
	struct sockaddr_in address;

	if ((sockfd = socket(m_domain, m_type, 0)) == 0)
	{
		std::cerr << "Server socket creation failed!" << std::endl;
		exit(1);
	}

	bzero((char *) &address, sizeof(address));
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_family = m_domain;
	address.sin_port = htons(m_port);

	if (bind(sockfd, (struct sockaddr *) &address, sizeof(address)) < 0)
	{
		std::cerr << "Server socket binding failed!";
		exit(1);
	}

	if (listen(sockfd, m_backlog) < 0)
	{
		std::cerr << "Server socket listen failed!" << std::endl;
		exit(1);
	}

	std::thread th[m_threads];

	int i = 0;
	while(1)
	{
		if(i == m_threads)
		{
			i = 0;
		}
		if(!th[i].joinable())
		{
			th[i] = std::thread(handle_request, sockfd, &address, this);
		}
		else
		{
			th[i].join();
		}
		i++;
	}
}

int main(int argc, char* argv[])
{
	/*
        *  Server configuration can be specified in a file or via command line
        *  such as server threads, backlog_size, protocol_family, protocol_type and other configurations if required
        *
        *  Currently using the default values for simplicity and not provided options to configure those
        *
        *  Usage: ./server port throttling_conf_file
        */

        if(argc < 3)
        {
                std::cerr << "Usage: ./server port throttling_conf_file" << std::endl;
                exit(1);
        }

	int port = atoi(argv[1]);
	std::string filename = argv[2];

	Server s1(port, AF_INET, SOCK_STREAM);
	s1.configure(filename);
	s1.run();
}
