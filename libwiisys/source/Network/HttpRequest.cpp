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

HttpRequest::HttpRequest() {
	sockfd = -1;
	NetworkUtility::GetIp();
}

HttpRequest::HttpRequest(const std::string& url) {
	sockfd = -1;
	NetworkUtility::GetIp();
	SetRequest(url);
}

void HttpRequest::Connect(string hostname) {
	struct hostent *he;
	struct sockaddr_in sa;

	s32 ret;

	/* Close socket if it is already open */
	if (sockfd >= 0)
		net_close(sockfd);

	/* Create socket */
	sockfd = net_socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	if (sockfd < 0)
		throw SystemException("Error openning socket !", sockfd);

	/* Get host by name */
	he = net_gethostbyname(hostname.c_str());
	if (!he)
		throw Exception("Error getting host name !");

	/* Setup socket */
	memcpy(&sa.sin_addr, he->h_addr_list[0], he->h_length);
	sa.sin_family = AF_INET;
	sa.sin_port = htons(NETWORK_PORT);

	ret = net_connect(sockfd, (struct sockaddr *) &sa, sizeof(sa));
	if (ret < 0)
		throw SystemException("Connection error !", ret);
}

void HttpRequest::SetRequest(const string& url) {
	_url = url;
	_hostName = _url.substr(7, _url.find_first_of('/', 7) - 7);
	_path = url.substr(_hostName.size() + 7, string::npos);
}

u32 HttpRequest::GetResponseLength() {
	if (_path.length() == 0 || _hostName.length() == 0)
		throw Exception("The request isn't properly initialised.");

	char buf[1024], request[256];

	s32 ret;

	stringstream fullPath;
	fullPath << _path;

	if (!_params.empty()) {
		bool isFirstParam = true;
		fullPath << "?";
		for (map<string, string>::iterator ite = _params.begin(); ite
				!= _params.end(); ++ite) {
			if (!isFirstParam)
				fullPath << "&";
			fullPath << NetworkUtility::URLEncode(ite->first) << "="
					<< NetworkUtility::URLEncode(ite->second);
			isFirstParam = false;
		}
	}

	/* Generate HTTP request */
	sprintf(request,
			"GET %s HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n",
			fullPath.str().c_str(), _hostName.c_str());

	/* Connect to server */
	Connect(_hostName);

	/* Send request */
	ret = net_send(sockfd, request, strlen(request), 0);
	if (ret < 0)
		throw SystemException("Error sending request.", ret);

	/* Clear buffer */
	memset(buf, 0, sizeof(buf));

	/* Read HTTP header */
	for (u32 cnt = 0; !strstr(buf, "\r\n\r\n"); cnt++)
		if (net_recv(sockfd, buf + cnt, 1, 0) <= 0)
			throw Exception("Error reading http header");

	/* HTTP request OK? */
	if (!(strstr(buf, "HTTP/1.1 200 OK") || strstr(buf, "HTTP/1.0 200 OK")))
		throw Exception("The response status indicate an error.");

	/* Retrieve content size */
	char *ptr = strstr(buf, "Content-Length:");
	if (!ptr)
		throw Exception("Error retrieving response lengt");

	u32 length;
	sscanf(ptr, "Content-Length: %u", &length);
	return length;
}

s32 HttpRequest::Read(Buffer& b, u32 len) {
	u32 totalRead = 0;
	while (totalRead < len) {
		/* Size to read */
		u32 size = len - totalRead;
		if (size > BLOCK_SIZE)
			size = BLOCK_SIZE;

		/* Read network data */
		void* tempBuffer = memalign(32, size);
		s32 nbRead = net_read(sockfd, tempBuffer, size);
		if (nbRead < 0) {
			free(tempBuffer);
			throw SystemException("Error reading http response.", nbRead);
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

s32 HttpRequest::Write(Buffer& b) {
	u32 totalWritten = 0;

	while (totalWritten < b.Length()) {
		/* Size to read */
		u32 size = b.Length() - totalWritten;
		if (size > BLOCK_SIZE)
			size = BLOCK_SIZE;

		/* Write network data */
		s32 nbWritten = net_write(sockfd, (char*) b.Content() + totalWritten,
				size);
		if (nbWritten < 0)
			throw SystemException("Error writing data to http socket.", nbWritten);

		/* Write finished */
		if (nbWritten == 0)
			break;

		totalWritten += nbWritten;
	}

	return totalWritten;
}

HttpRequest::~HttpRequest() {
	if (sockfd >= 0) {
		net_close(sockfd);
		sockfd = -1;
	}
}

Buffer HttpRequest::GetResponse() {
	u32 len = GetResponseLength();
	Buffer response;

	Read(response, len);

	return response;
}

Buffer HttpRequest::GetResponse(const Buffer& sha) {
	Buffer response = GetResponse();
	if (!response.ValidateSHA1(sha))
		throw Exception("SHA encryption is not valid.");

	return response;
}

Buffer HttpRequest::GetResponse(const std::string& shaUrl) {
	if (shaUrl != "") {
		HttpRequest sha(shaUrl);
		Buffer bsha = sha.GetResponse();
		return GetResponse(bsha);
	}

	return GetResponse();
}

void HttpRequest::AddParameter(const string& key, const string& value) {
	_params[key] = value;
}

std::string HttpRequest::GetType()
{
	return "Libwiisys::Network::HttpRequest,"+Object::GetType();	
}
