#include "Config.h"
#include <fstream>

bool Config::loadConfig()
{
	std::ifstream file;
	std::string line;
	
	file.open(m_fileName);
	while(std::getline(file, line))
	{
		// Assuming configuration file is correctly populated
		// Can add checks while reading conf file
		// example contents in the file: 
		// User1:5
		// User2:10

		std::string userName;
		int maxRequests;
		userName = line.substr(0,line.find(":"));
		maxRequests = stoi(line.substr(line.find(":")+1));

		User u(userName, maxRequests);
		m_config.insert(std::pair<std::string, User>(userName, u));
	}
	file.close();
	return true;
}
