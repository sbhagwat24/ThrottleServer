#include "Client.h"
#include <netinet/in.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <netdb.h> 

void Client::run(const std::string& message)
{
	int sockfd = 0;
        struct sockaddr_in address;
        bzero((char *) &address, sizeof(address));

        if ((sockfd = socket(m_domain, m_type, 0)) == 0)
        {
                std::cerr << "Client socket creation failed!" << std::endl;
                exit(1);
        }

	struct hostent *server = gethostbyname(m_serverName.c_str());
	if (server == NULL)
	{
		std::cerr << "Invalid server name: " << m_serverName << std::endl;
		exit(1);
	}
	bcopy((char *)server->h_addr, (char *)&address.sin_addr.s_addr, server->h_length);
        address.sin_family = m_domain;
        address.sin_port = htons(m_port);

	if (connect(sockfd, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		std::cerr << "Client socket connect failed!" << std::endl;
		exit(1);
	}

	int n = write(sockfd, message.c_str(), message.length());
	if (n == 0)
	{
		std::cerr << "Socket write failed" << std::endl;
		exit(1);
	}

	// Assuming response fits in this size
	char response[50] = {0};
	n = read(sockfd, response, sizeof(response));
	if( n > 0)
	{
		std::cout << response << std::endl;
	}
	else
	{
		std::cerr << "Socket read failed" << std::endl;
		exit(1);
	}
	close(sockfd);
}

int main(int argc, char *argv[])
{
	/* 
 	*  Client configuration can be specified in a file or via command line
 	*  such as protocol_family, protocol_type and other configurations if required
 	*
 	*  Currently using the default values for simplicity and not provided options to configure those
 	*
 	*  Usage: ./client servername port request
 	*
 	*  In this example, request will be just user name. Also spaces are not allowed in user name for now
 	*/
	
	if(argc < 4)
	{
		std::cerr << "Usage: ./client servername port request" << std::endl;
		exit(1);
	}

	std::string serverName = argv[1];
	int port = atoi(argv[2]);
	std::string request = argv[3];	
	
	// We need to add checks for individual arguments to conform their correctness
	// Currently assuming that everything is as per requirements

	Client c1(serverName, port);
	while(1)
	{
		c1.run(request);
		// Sleep for 1000 micro secs before sending another request
		usleep(1000);
	}

	return 0;
}
