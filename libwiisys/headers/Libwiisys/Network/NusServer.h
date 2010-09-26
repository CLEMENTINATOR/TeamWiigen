#ifndef _NUSSERVER_H_
#define _NUSSERVER_H_

#include <string>
#include "HttpRequest.h"

#define NUS_HOSTNAME	"http://nus.cdn.shop.wii.com"
#define NUS_PATH		"/ccs/download/"

namespace Libwiisys {namespace Network {

		/**
		 * \class NusServer
		 * \brief This class allow the download on NUS servers
		 * \author Arasium, Teton, Fanta
		 * \version 1.0
		 */
		class NusServer : public HttpRequest
		{
		public:
			virtual std::string GetType();
			/**
			 * \brief Constructor
			 * \param titleId The title id
			 * \param fileName The file you want to download ( ex : tmd,cetk,0000000c ect..)
			 **/
			NusServer(u64 titleId, const std::string &fileName);
		};

	}}

#endif
