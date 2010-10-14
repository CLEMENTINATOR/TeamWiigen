#include <ogc/ios.h>
#include <sstream>

#include <Libwiisys/logging/Log.h>
#include <sciifii/business/IosReloader.h>
#include <Libwiisys/system/Title.h>

using namespace std;
using namespace Libwiisys::System;

using namespace Libwiisys::Logging;

IosReloader::IosReloader(u32 ios)
    : Installer(),
    _id(ios)
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
}
void IosReloader::SendToLog()
{
  stringstream txt;
  txt << "IOSReloader("<<_id<<" )";
  Log::WriteLog(Log_Info,txt.str());
}
