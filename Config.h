#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <string>
#include <map>
#include "User.h"

class Config
{
	std::string m_fileName; // Configuration file
public:
	std::map<std::string, User> m_config; // username -> User information(config details)

	Config(std::string file) :
		m_fileName(file) {};

	bool loadConfig();
};

#endif
