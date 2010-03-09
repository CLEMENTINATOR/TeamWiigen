#include <com/NusServer.h>

#include <iomanip>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

NusServer::NusServer(u64 titleId, const string &fileName)
  : NetworkRequest()
{
	stringstream netpath;

	netpath << NUS_HOSTNAME << NUS_PATH << setw(16) << setfill('0') << hex << titleId <<"/" <<fileName;

	SetRequest(netpath.str());
}
