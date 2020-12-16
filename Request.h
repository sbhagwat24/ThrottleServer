#ifndef _REQUEST_H_
#define _REQUEST_H_

class Request
{
public:
	enum class reqType {
		LOGIN,
		CREATE_ACCOUNT,
		CREATE_BUCKET,
		UPLOAD_OBJECT,
		DOWNLOAD_OBJECT
	};

	Request(reqType requestType) : m_id(0), m_epochTime(std::time(0)), m_type(requestType) {}

	time_t getTime() const { return m_epochTime; };

private:
	const int m_id;
	const time_t m_epochTime;
	const reqType m_type;
};

#endif
