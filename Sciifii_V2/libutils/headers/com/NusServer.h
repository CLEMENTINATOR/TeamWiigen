#ifndef _NUSSERVER_H_
#define _NUSSERVER_H_

#include <string>
#include "NetworkRequest.h"

#define NUS_HOSTNAME	"http://nus.cdn.shop.wii.com"
#define NUS_PATH		"/ccs/download/"

class NusServer : public NetworkRequest
{
public:
	NusServer(u64 titleId, const std::string &fileName);
};

#endif
