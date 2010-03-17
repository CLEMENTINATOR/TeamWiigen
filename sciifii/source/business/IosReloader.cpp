#include "IosReloader.h"

#include <libutils/fs/Device.h>
#include <ogc/ios.h>
#include <sstream>
#include <libutils/system/Title.h>
using namespace std;

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
	Title::ReloadIOS(249);
	if(_identify)
	  Identification::IdentifyAs(_type);

}
