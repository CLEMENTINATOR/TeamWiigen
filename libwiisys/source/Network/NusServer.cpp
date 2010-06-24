#include <libwiisys.h>

#include <iomanip>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;
using namespace Libwiisys::Network;
using namespace Libwiisys::Exceptions;
using namespace Libwiisys;

/**
*\brief Constructor
*\param titleId The title id
*\param fileName The file you want to download ( ex : tmd,cetk,0000000c ect..)
**/
NusServer::NusServer(u64 titleId, const string &fileName)
  : HttpRequest()
{
	stringstream netpath;

	netpath << NUS_HOSTNAME << NUS_PATH << setw(16) << setfill('0') << hex << titleId <<"/" <<fileName;

	SetRequest(netpath.str());
}
