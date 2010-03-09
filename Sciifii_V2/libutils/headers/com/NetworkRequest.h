#ifndef _TEST_NETWORK_REQUEST_
#define _TEST_NETWORK_REQUEST_

#include <ogcsys.h>
#include <string>
#include "../Object.h"
#include "Buffer.h"

/*! \class NetworkRequest
 * \brief This class allow the use of HTTP (GET) request
 * \author Arasium, Teton, Fanta
 * \version 1.0
 *
 * The NetworkRequest class allow the user to use HTTP request (GET)
 * and to download the results.
 */


class NetworkRequest : public Object
{
public:
	NetworkRequest();
	NetworkRequest(const std::string& url);
	~NetworkRequest();
	static std::string GetIp(void);
	Buffer GetResponse();
	void SetRequest(const std::string& url);

private:
	s32 sockfd;
	std::string _url;
	std::string _hostName;
	std::string _path;
	void Connect(std::string hostname);
	s32 Read(Buffer& b, u32 len);
	s32 Write(Buffer &b);
	u32 GetResponseLength();
};

#endif
