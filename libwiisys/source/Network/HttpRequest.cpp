#include <network.h>
#include <cstring>
#include <cstdio>
#include <malloc.h>
#include <libwiisys.h>

#define BLOCK_SIZE		8192
#define NETWORK_PORT 80

using namespace std;
using namespace Libwiisys::Network;
using namespace Libwiisys::Exceptions;
using namespace Libwiisys;

/*!
 * \brief Constructor
 *
 */
HttpRequest::HttpRequest()
{
	sockfd=-1;
	NetworkUtility::GetIp();
}

/*!
 * \brief Overloaded constructor
 * \param url the full url for the request
 *
 */
HttpRequest::HttpRequest(const std::string& url)
{
	sockfd=-1;
	NetworkUtility::GetIp();
	SetRequest(url);
}


/*!
 * \brief Connect
 * \param hostname The hostname of the server
 */
void HttpRequest::Connect(string hostname)
{
	struct hostent *he;
	struct sockaddr_in sa;

	s32 ret;

	/* Close socket if it is already open */
	if (sockfd >= 0)
		net_close(sockfd);

	/* Create socket */
	sockfd = net_socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	if (sockfd < 0)
		throw  Exception("Error openning socket !",sockfd);

	/* Get host by name */
	he = net_gethostbyname(hostname.c_str());
	if (!he)
		throw  Exception("Error getting host name !",-1);

	/* Setup socket */
	memcpy(&sa.sin_addr, he->h_addr_list[0], he->h_length);
	sa.sin_family = AF_INET;
	sa.sin_port = htons(NETWORK_PORT);

	ret = net_connect(sockfd, (struct sockaddr *)&sa, sizeof(sa));
	if (ret < 0)
		throw  Exception("Connection error !",ret);
}

/*!
 * \brief Set an new http request
 * \param url the server url (needs to begin by "http://www.)
 */
void HttpRequest::SetRequest(const string& url)
{
	_url = url;
	_hostName = _url.substr(7,_url.find_first_of('/',7) - 7);
	_path = url.substr(_hostName.size() + 7,string::npos);
}

/*!
 * \brief Get the length of the network response
 * \return The length of the contents
 *
 */
u32 HttpRequest::GetResponseLength()
{
	if(_path.length() == 0 || _hostName.length() == 0)
		throw Exception("The request isn't properly initialised.", -1);

	char buf[1024], request[256];

	s32 ret;

	stringstream fullPath;
	fullPath << _path;

	if(!_params.empty())
	{
		bool isFirstParam = true;
		fullPath << "?";
		for(map<string, string>::iterator ite = _params.begin(); ite != _params.end(); ++ite )
		{
			if(!isFirstParam)
				fullPath << "&";
			fullPath << NetworkUtility::URLEncode(ite->first) << "=" << NetworkUtility::URLEncode(ite->second);
			isFirstParam = false;
		}
	}

	/* Generate HTTP request */
	sprintf(request, "GET %s HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n", fullPath.str().c_str(),_hostName.c_str());

	/* Connect to server */
	Connect(_hostName);

	/* Send request */
	ret = net_send(sockfd, request, strlen(request), 0);
	if (ret < 0)
		throw Exception("Error sending request.", ret);

	/* Clear buffer */
	memset(buf, 0, sizeof(buf));

	/* Read HTTP header */
	for (u32 cnt = 0; !strstr(buf, "\r\n\r\n"); cnt++)
		if (net_recv(sockfd, buf + cnt, 1, 0) <= 0)
			throw Exception("Error reading http header", -1);

	/* HTTP request OK? */
	if (!(strstr(buf, "HTTP/1.1 200 OK") || strstr(buf, "HTTP/1.0 200 OK")))
		throw Exception("The response status indicate an error.", -1);

	/* Retrieve content size */
	char *ptr = strstr(buf, "Content-Length:");
	if (!ptr)
		throw Exception("Error retrieving response lengt", -1);

	u32 length;
	sscanf(ptr, "Content-Length: %u", &length);
	return length;
}

/*!
 * \brief Read data from the serv
 * \param b The Buffer where you want to store the readed data
 *\param len The len of the readed content
 * \return The length read
 *
 */
s32 HttpRequest::Read(Buffer& b, u32 len)
{
	u32 totalRead = 0;
	while(totalRead < len)
	{
		/* Size to read */
		u32 size = len - totalRead;
		if (size > BLOCK_SIZE)
			size = BLOCK_SIZE;

		/* Read network data */
		void* tempBuffer = memalign(32, size);
		s32 nbRead = net_read(sockfd, tempBuffer, size);
		if (nbRead < 0)
		{
			free(tempBuffer);
			throw Exception("Error reading http response.", nbRead);
		}

		b.Append(tempBuffer, nbRead);
		free(tempBuffer);

		/* Read finished */
		if (nbRead == 0)
			break;

		totalRead += nbRead;
	}

	return totalRead;
}

/*!
 * \brief Send data to the serv
 * \param b The buffer to be writted
 * \return The length writen
 *
 */
s32 HttpRequest::Write(Buffer& b)
{
	u32 totalWritten = 0;

	while(totalWritten < b.Length())
	{
		/* Size to read */
		u32 size = b.Length() - totalWritten;
		if (size > BLOCK_SIZE)
			size = BLOCK_SIZE;

		/* Write network data */
		s32 nbWritten = net_write(sockfd, (char*)b.Content() + totalWritten, size);
		if (nbWritten < 0)
			throw Exception("Error writing data to http socket.", nbWritten);

		/* Write finished */
		if (nbWritten == 0)
			break;

		totalWritten += nbWritten;
	}

	return totalWritten;
}

/*!
 * \brief Destructor
 */
HttpRequest::~HttpRequest()
{
	if (sockfd >= 0)
	{
		net_close(sockfd);
		sockfd=-1;
	}
}

/*!
 * \brief Get the server response
 * \return A buffer containing the reponse
 */
Buffer HttpRequest::GetResponse()
{
	u32 len = GetResponseLength();
	Buffer response;

	Read(response, len);

	return response;
}

/*!
 * \brief Get the server response and check sha1 hash
 *\param sha The sha buffer
 * \return A buffer containing the reponse
 */
Buffer HttpRequest::GetResponse(const Buffer& sha)
{
	Buffer response = GetResponse();
	if(!response.ValidateSHA1(sha))
		throw Exception("SHA encryption is not valid.", -1);

	return response;
}

/*!
 * \brief Get the server response and check sha1 hash
 *\param shaUrl The sha1 url
 * \return A buffer containing the reponse
 */
Buffer HttpRequest::GetResponse(const std::string& shaUrl)
{
	if(shaUrl != "")
	{
		HttpRequest sha(shaUrl);
		Buffer bsha = sha.GetResponse();
		return GetResponse(bsha);
	}

	return GetResponse();
}

void HttpRequest::AddParameter(const string& key, const string& value)
{
	_params[key] = value;
}
