#include <network.h>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <malloc.h>
#include <Libwiisys/Network/HttpRequest.h>
#include <Libwiisys/Network/NetworkUtility.h>
#include <Libwiisys/Exceptions/Exception.h>
#include <Libwiisys/Exceptions/SystemException.h>

#define BLOCK_SIZE  8192
#define NETWORK_PORT 80

using namespace std;
using namespace Libwiisys::Network;
using namespace Libwiisys::Exceptions;
using namespace Libwiisys;

HttpRequest::HttpRequest()
{
  sockfd = -1;
  NetworkUtility::GetIp();
}

HttpRequest::HttpRequest(const std::string& url)
{
  sockfd = -1;
  NetworkUtility::GetIp();
  SetRequest(url);
}

void HttpRequest::Connect(string hostname)
{
  struct hostent *he;
  struct sockaddr_in sa;

  s32 ret;

  NetworkUtility::Lock();

  /* Close socket if it is already open */
  if (sockfd >= 0)
  {
    net_close(sockfd);
    sockfd = -1;
  }

  /* Create socket */
  sockfd = net_socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
  if (sockfd < 0)
    throw SystemException("Error openning socket !", sockfd);

  /* Get host by name */
  he = net_gethostbyname(hostname.c_str());
  if (!he)
    throw Exception("Error getting host name : "+hostname);

  /* Setup socket */
  memcpy(&sa.sin_addr, he->h_addr_list[0], he->h_length);
  sa.sin_family = AF_INET;
  sa.sin_port = htons(NETWORK_PORT);

  ret = net_connect(sockfd, (struct sockaddr *) &sa, sizeof(sa));
  if (ret < 0)
    throw SystemException("Connection error !", ret);
}

void HttpRequest::SetRequest(const string& url)
{
  _url = url;
  _hostName = _url.substr(7, _url.find_first_of('/', 7) - 7);
  _path = url.substr(_hostName.size() + 7, string::npos);
  _params.clear();
}

u32 HttpRequest::GetResponseLength()
{
  if (_path.length() == 0 || _hostName.length() == 0)
    throw Exception("The request isn't properly initialised.");
	
  s32 ret;
  stringstream request, response;
  char responseChar;
  
  request << "GET " << _path;

  if (!_params.empty())
  {
    bool isFirstParam = true;
    request << "?";
    for (map<string, string>::iterator ite = _params.begin(); ite != _params.end(); ++ite)
    {
      if (!isFirstParam)
        request << "&";
		
      request << NetworkUtility::URLEncode(ite->first) << "=" << NetworkUtility::URLEncode(ite->second);
      isFirstParam = false;
    }
  }

  /* Generate HTTP request */
  request << " HTTP/1.1\r\nHost: " << _hostName << "\r\nConnection: close\r\n\r\n";

  /* Connect to server */
  Connect(_hostName);

  /* Send request */
  ret = net_send(sockfd, request.str().c_str(), request.str().length(), 0);
  if (ret < 0)
    throw SystemException("Error sending request.", ret);

  /* Read HTTP header */
  while(response.str().find("\r\n\r\n") == string::npos)
  {
    if (net_recv(sockfd, &responseChar, 1, 0) <= 0)
      throw Exception("Error reading http header");
	else
		response << responseChar;
  }

  /* HTTP request OK? */
  u32 code;
  u32 position = response.str().find("HTTP/1.1");
  if (position != string::npos)
    sscanf(response.str().substr(position).c_str(), "HTTP/1.1 %u", &code);
  else
    throw Exception("No http 1.1 response");

  if (code != 200)
    throw Exception("Error http "+code);

  /* Retrieve content size */
  
  position = response.str().find("Content-Length:");
  if (position == string::npos)
	position = response.str().find("content-Length:");
	
  if(position == string::npos)
	throw Exception("Error retrieving response lengt");
		
  u32 length;
  sscanf(response.str().substr(position).c_str(), "Content-Length: %u", &length);
  return length;
}

s32 HttpRequest::Read(Buffer& b, u32 len)
{
  u32 totalRead = 0;
  while (totalRead < len)
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

s32 HttpRequest::Write(Buffer& b)
{
  u32 totalWritten = 0;

  while (totalWritten < b.Length())
  {
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

HttpRequest::~HttpRequest()
{
  Disconnect();
}

Buffer HttpRequest::GetResponse()
{
  u32 len = GetResponseLength();
  Buffer response;

  Read(response, len);

  return response;
}

Buffer HttpRequest::GetResponse(const Buffer& sha)
{
  Buffer response = GetResponse();
  if (!response.ValidateSHA1(sha))
    throw Exception("SHA encryption is not valid.");

  return response;
}

Buffer HttpRequest::GetResponse(const std::string& shaUrl)
{
  if (shaUrl != "")
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

std::string HttpRequest::GetType()
{
  return "Libwiisys::Network::HttpRequest,"+Object::GetType();
}

void HttpRequest::Disconnect()
{
  if (sockfd >= 0)
  {
    net_close(sockfd);
    sockfd = -1;
    NetworkUtility::Release();
  }
}
