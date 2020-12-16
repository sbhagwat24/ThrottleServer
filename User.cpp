#include "User.h"

void User::reset(const Request& req)
{
	m_lastRequestTime = req.getTime();
	m_validTokens = m_maxRequestPerSecond;
}

bool User::getToken(const Request& req)
{
	if (!m_lastRequestTime)
	{
		// User has not yet requested for any token
		reset(req);
		--m_validTokens;
		return true;
	}
	else if (m_lastRequestTime == req.getTime())
	{
		if (m_validTokens)
		{
			// User still has valid tokens left
			--m_validTokens;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		// Last and current request time differ.
		// Reset tokens
		reset(req);
		--m_validTokens;
		return true;
	}
}
