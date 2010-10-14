#include <libwiisys/Network/NusServer.h>

#include <iomanip>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;
using namespace Libwiisys::Network;
using namespace Libwiisys;

NusServer::NusServer(u64 titleId, const string &fileName) :
    HttpRequest()
{
  stringstream netpath;

  netpath << NUS_HOSTNAME << NUS_PATH << setw(16) << setfill('0') << hex
  << titleId << "/" << fileName;

  SetRequest(netpath.str());
}


std::string NusServer::GetType()
{
  return "Libwiisys::Network::HttpRequest,"+HttpRequest::GetType();
}
