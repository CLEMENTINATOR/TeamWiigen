#ifndef NETWORKUTILITY_H_
#define NETWORKUTILITY_H_

#include <string>

namespace Libwiisys { namespace Network {

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

}}

#endif /* NETWORKUTILITY_H_ */
