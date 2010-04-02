#ifndef _NUSSERVER_H_
#define _NUSSERVER_H_

#include <string>
#include "NetworkRequest.h"

#define NUS_HOSTNAME	"http://nus.cdn.shop.wii.com"
#define NUS_PATH		"/ccs/download/"

/*! \class NusServer
 * \brief This class allow the download on NUS servers
 * \author Arasium, Teton, Fanta
 * \version 1.0
 *
 * The NetworkRequest class allow user to download title on NUS servers
 */
class NusServer : public NetworkRequest
{
public:
	NusServer(u64 titleId, const std::string &fileName);
};

#endif
