#include "IosReloader.h"
#include "../Config.h"

#include <libwiisys.h>
#include <ogc/ios.h>
#include <sstream>

using namespace std;
using namespace Libwiisys::System;
using namespace Libwiisys::System::Security;

using namespace Libwiisys::Logging;

IosReloader::IosReloader(u32 ios)
: Installer(),
  _id(ios),
  _identify(false)
{}

IosReloader::IosReloader(u32 ios, UserType type)
: Installer(),
  _id(ios),
  _identify(true),
  _type(type)
{}

bool IosReloader::Prepare()
{
  return true;
}

void IosReloader::Install()
{
	stringstream txt;
	txt << "Reloading under IOS" << _id;
	OnProgress(txt.str(), 1);
	Title::ReloadIOS(_id);
	if(_identify)
	  Identification::IdentifyAs(_type);
}
void IosReloader::SendToLog()
{
	stringstream txt;
		txt << "IOSReloader("<<_id<<" )";
	Log::WriteLog(Log_Info,txt.str());
}
