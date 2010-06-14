/*
 * NetworkUtility.h
 *
 *  Created on: 10 juin 2010
 *      Author: Clement
 */

#ifndef NETWORKUTILITY_H_
#define NETWORKUTILITY_H_
#include <string>


class NetworkUtility {
public:
	NetworkUtility();
	virtual ~NetworkUtility();
	static std::string GetIp(void);
	static NetworkUtility &Current();
	static std::string URLEncode(std::string s);
	static void Deinit();
private :
  std::string _hostIp;
	static bool& Initialized();

};

#endif /* NETWORKUTILITY_H_ */
