#ifndef _USER_H_
#define _USER_H_

#include <iostream>
#include <ctime>
#include "Request.h"

class User
{
	const std::string m_name;
        const int m_maxRequestPerSecond;
        int m_validTokens;	// Valid tokens left for m_lastRequestTime
        time_t m_lastRequestTime;

	/*
	 * Reset user requests information.
	 * m_lastRequestTime    : Time when last request was made by the user
	 * m_validTokens  	: Valid tokens left for the user at m_lastRequestTime
	*/
	void reset(const Request& req);

public:
	User(std::string name, int rate)
		: m_name(name), m_maxRequestPerSecond(rate), m_validTokens(0), m_lastRequestTime(0) {}

	/*
	 * Checks if user has exhausted the max_requests/sec allowed
	 * Return:
	 *      true : User has valid tokens left for current time
	 *      false : User has exhausted all tokens for current time
	 *
	 * Currently we are not throttling on the basis of request type
	 * We can have different throttling logic for different request types
	*/
	bool getToken(const Request& req);
};

#endif
