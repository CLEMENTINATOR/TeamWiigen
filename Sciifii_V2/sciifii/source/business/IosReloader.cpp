#include "IosReloader.h"

#include <libutils/fs/Device.h>
#include <ogc/ios.h>
#include <sstream>

using namespace std;

IosReloader::IosReloader(u32 ios, const string& deviceToManage)
: Installer(),
  _id(ios),
  _device(deviceToManage),
  _identify(false)
{}

IosReloader::IosReloader(u32 ios, UserType type, const string& deviceToManage)
: Installer(),
  _id(ios),
  _device(deviceToManage),
  _identify(true),
  _type(type)
{}

bool IosReloader::Prepare()
{
  return true;
}

void IosReloader::Install()
{
	if(_device.length() > 0)
	{
		Device::UnMount(_device);
	}
	
	stringstream txt;
	txt << "Reloading under IOS" << _id;
	OnProgress(txt.str(), 1);
	IOS_ReloadIOS(_id);
	
	if(_device.length() > 0)
	{
		Device::Mount(_device);
	}
	
	if(_identify)
	  Identification::IdentifyAs(_type);
}
