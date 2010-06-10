#ifndef _TEST_NETWORK_REQUEST_
#define _TEST_NETWORK_REQUEST_

#include <map>
#include <ogcsys.h>
#include <string>
#include "../Object.h"
#include "Buffer.h"
#include <sstream>

/*! \class NetworkRequest
 * \brief This class allow the use of HTTP (GET) request
 * \author Arasium, Teton, Fanta
 * \version 1.0
 *
 * The NetworkRequest class allow the user to use HTTP request (GET)
 * and to download the results.
 */


class HttpRequest : public Object
{
public:
	HttpRequest();
	HttpRequest(const std::string& url);
	~HttpRequest();
	Buffer GetResponse();
	Buffer GetResponse(const Buffer& sha);
	Buffer GetResponse(const std::string& shaUrl);
	void SetRequest(const std::string& url);
  void AddParameter(const std::string& key, const std::string& value);
  
private:
	s32 sockfd;
	std::string _url;
	std::string _hostName;
	std::string _path;
  std::map<std::string, std::string> _params;
  
	void Connect(std::string hostname);
	s32 Read(Buffer& b, u32 len);
	s32 Write(Buffer &b);
	u32 GetResponseLength();
};

#endif
