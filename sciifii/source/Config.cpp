#include "Config.h"
#include <libutils/com/NetworkRequest.h>
#include <libutils/system/Title.h>
#include <ogc/conf.h>
#include <cstdlib>

using namespace std;

Config::Config()
: _hasNetwork(false),
  _downgradeIos(15),
  _downgradeIosRevision(257),
  _truchaIos(36),
  _ciosSlot(249),
  _ciosRevision(17),
  _corp(),
  _systemTitleList(),
  _updateList(),
  _restoreTrucha(true),
  _installCios(true),
  _installCorp(true),
  _updateSystem(true),
  _installGX(true)
{
	try
	{
		NetworkRequest::GetIp();
		_hasNetwork = true;
	}
	catch(...)
	{
		_installGX = false;
	}
	
	s32 region = CONF_GetRegion();
	if(region == CONF_REGION_CN)
		exit(0);
		
	_corp.push_back((ciosDesc){	9,	60,	6174,	13,	0,	true,	false,	true,	""});
	_corp.push_back((ciosDesc){	11,	60,	6174,	13, 0,	true,	false,	true,	""});
	_corp.push_back((ciosDesc){	17,	53,	5149,	17, 0,	false,	false,	true,	""});
	_corp.push_back((ciosDesc){	20,	60,	6174,	13, 0,	true,	false,	true,	""});
	_corp.push_back((ciosDesc){	21,	53,	5149,	17, 0,	false,	false,	true,	""});
	_corp.push_back((ciosDesc){	28,	28,	1293,	17, 0, 	false,	false,	false,	""});
	_corp.push_back((ciosDesc){	30,	60,	6174,	13,	0, 	true,	false,	true,	""});
	_corp.push_back((ciosDesc){	33,	33,	2834,	17, 0, 	false,	false,	false,	""});
	_corp.push_back((ciosDesc){	35,	35,	3092,	17, 0, 	true,	false,	false,	""});
	_corp.push_back((ciosDesc){	36,	36,	3094,	13,	0, 	true,	true,	false,	""});
	_corp.push_back((ciosDesc){	37,	37,	3612,	17, 0,	true,	true,	true,	""});
	_corp.push_back((ciosDesc){	38,	38,	3610,	17, 17, false,	false,	false,	""});
	_corp.push_back((ciosDesc){	40,	60,	6174,	13,	0, 	true,	false,	true,	""});
	_corp.push_back((ciosDesc){	41,	41,	3091,	17,	0, 	false,	false,	true,	""});
	_corp.push_back((ciosDesc){	43,	43,	3091,	17,	0, 	false,	false,	true,	""});
	_corp.push_back((ciosDesc){	45,	45,	3091,	17,	0, 	false,	false,	true,	""});
	_corp.push_back((ciosDesc){	46,	46,	3093,	17,	0, 	false,	false,	true,	""});
	_corp.push_back((ciosDesc){	50,	50,	4889,	13,	0, 	true,	false,	true,	""});
	_corp.push_back((ciosDesc){	52,	52,	5661,	13,	0, 	true,	false,	true,	""});
	_corp.push_back((ciosDesc){	53,	53,	5149,	17, 0, 	false,	false,	true,	""});
	_corp.push_back((ciosDesc){	55,	55,	5149,	17, 0, 	false,	false,	true,	""});
	_corp.push_back((ciosDesc){	56,	56,	5146,	17, 0, 	false,	false,	true,	"http://dmanspokehackland.webs.com/cIOSCORP/IOS56-64-v5146.wad"}); //need url
	_corp.push_back((ciosDesc){	58,	58,	5918,	17,	0,	false,	false,	false, 	"http://dmanspokehackland.webs.com/cIOSCORP/IOS58-64-v5918.wad"});
	_corp.push_back((ciosDesc){	60,	60,	6174,	13,	0, 	true,	false,	true,	""});
	_corp.push_back((ciosDesc){	70,	60,	6174,	13,	0, 	true,	false,	true,	""});

	_systemTitleList.push_back((titleDescriptor){ 0x0000000100000004ULL, 0xff00,	false});
	_systemTitleList.push_back((titleDescriptor){ 0x0000000100000009ULL, 0x030a,	false});
	_systemTitleList.push_back((titleDescriptor){ 0x000000010000000aULL, 0x0300,	false});
	_systemTitleList.push_back((titleDescriptor){ 0x000000010000000bULL, 0x0100,	false});
	_systemTitleList.push_back((titleDescriptor){ 0x000000010000000cULL, 0x010d,	false});
	_systemTitleList.push_back((titleDescriptor){ 0x000000010000000dULL, 0x0111,	false});
	_systemTitleList.push_back((titleDescriptor){ 0x000000010000000eULL, 0x0208,	false});
	_systemTitleList.push_back((titleDescriptor){ 0x000000010000000fULL, 0x020b,	false});
	_systemTitleList.push_back((titleDescriptor){ 0x0000000100000010ULL, 0x0200,	false});
	_systemTitleList.push_back((titleDescriptor){ 0x0000000100000011ULL, 0x0307,	false});
	_systemTitleList.push_back((titleDescriptor){ 0x0000000100000014ULL, 0x0100,	false});
	_systemTitleList.push_back((titleDescriptor){ 0x0000000100000015ULL, 0x030e,	false});
	_systemTitleList.push_back((titleDescriptor){ 0x0000000100000016ULL, 0x040d,	false});
	_systemTitleList.push_back((titleDescriptor){ 0x000000010000001cULL, 0x060e,	false});
	_systemTitleList.push_back((titleDescriptor){ 0x000000010000001eULL, 0x0b00,	false});
	_systemTitleList.push_back((titleDescriptor){ 0x000000010000001fULL, 0x0d15,	false});
	_systemTitleList.push_back((titleDescriptor){ 0x0000000100000021ULL, 0x0c13,	false});
	_systemTitleList.push_back((titleDescriptor){ 0x0000000100000022ULL, 0x0d14,	false});
	_systemTitleList.push_back((titleDescriptor){ 0x0000000100000023ULL, 0x0d15,	false});
	_systemTitleList.push_back((titleDescriptor){ 0x0000000100000024ULL, 0x0d17,	false});
	_systemTitleList.push_back((titleDescriptor){ 0x0000000100000025ULL, 0x0f1d,	false});
	_systemTitleList.push_back((titleDescriptor){ 0x0000000100000026ULL, 0x0f1b,	false});
	_systemTitleList.push_back((titleDescriptor){ 0x0000000100000029ULL, 0x0d14,	false});
	_systemTitleList.push_back((titleDescriptor){ 0x000000010000002BULL, 0x0d14,	false});
	_systemTitleList.push_back((titleDescriptor){ 0x000000010000002DULL, 0x0d14,	false});
	_systemTitleList.push_back((titleDescriptor){ 0x000000010000002EULL, 0x0d16,	false});
	_systemTitleList.push_back((titleDescriptor){ 0x0000000100000032ULL, 0x1400,	false});
	_systemTitleList.push_back((titleDescriptor){ 0x0000000100000033ULL, 0x1300,	false});
	_systemTitleList.push_back((titleDescriptor){ 0x0000000100000034ULL, 0x1700,	false});
	_systemTitleList.push_back((titleDescriptor){ 0x0000000100000035ULL, 0x151e,	false});
	_systemTitleList.push_back((titleDescriptor){ 0x0000000100000037ULL, 0x151e,	false});
	_systemTitleList.push_back((titleDescriptor){ 0x0000000100000038ULL, 0x151d,	false});
	_systemTitleList.push_back((titleDescriptor){ 0x0000000100000039ULL, 0x161d,	false});
	_systemTitleList.push_back((titleDescriptor){ 0x000000010000003dULL, 0x151d,	false});
	_systemTitleList.push_back((titleDescriptor){ 0x0000000100000046ULL, 0x1a1f,	false}); //the sysMenu 4.2 ios
	
	switch(region) //sysMenu
	{
		case CONF_REGION_JP:
			_systemTitleList.push_back((titleDescriptor){ 0x0000000100000002ULL, 0x01e0,	false});
			break;
		case CONF_REGION_US:
			_systemTitleList.push_back((titleDescriptor){ 0x0000000100000002ULL, 0x01e1,	false});
			break;
		case CONF_REGION_EU:
			_systemTitleList.push_back((titleDescriptor){ 0x0000000100000002ULL, 0x01e2,	false});
			break;
		case CONF_REGION_KR:
			_systemTitleList.push_back((titleDescriptor){ 0x0000000100000002ULL, 0x01e6,	false});
			break;
	}
	
	_systemTitleList.push_back((titleDescriptor){ 0x000000010000003cULL, 0x1900,	false}); //the ios60 stub is placed after the new SysMenu installation
	_systemTitleList.push_back((titleDescriptor){ 0x0000000100000100ULL, 0x0006,	false});
	_systemTitleList.push_back((titleDescriptor){ 0x0000000100000101ULL, 0x000a,	false});
	
	switch(region)  //channels
	{
		case CONF_REGION_JP:
			_systemTitleList.push_back((titleDescriptor){ 0x0001000248414141ULL, 0x0002,	false});  //Photo
			_systemTitleList.push_back((titleDescriptor){ 0x0001000248414241ULL, 0x0012,	false});  //Shopping
			_systemTitleList.push_back((titleDescriptor){ 0x0001000248414341ULL, 0x0006,	false});  //Mii channel
			_systemTitleList.push_back((titleDescriptor){ 0x000100024841464AULL, 0x0007,	false});  //weather
			_systemTitleList.push_back((titleDescriptor){ 0x000100024841474AULL, 0x0007,	false});  //news
			break;
		case CONF_REGION_US:
			_systemTitleList.push_back((titleDescriptor){ 0x0001000248414141ULL, 0x0002,	false});
			_systemTitleList.push_back((titleDescriptor){ 0x0001000248414241ULL, 0x0012,	false});
			_systemTitleList.push_back((titleDescriptor){ 0x0001000248414341ULL, 0x0006,	false});
			_systemTitleList.push_back((titleDescriptor){ 0x0001000248414645ULL, 0x0007,	false});
			_systemTitleList.push_back((titleDescriptor){ 0x0001000248414745ULL, 0x0007,	false});
			break;
		case CONF_REGION_EU:
			_systemTitleList.push_back((titleDescriptor){ 0x0001000248414141ULL, 0x0002,	false});
			_systemTitleList.push_back((titleDescriptor){ 0x0001000248414241ULL, 0x0012,	false});
			_systemTitleList.push_back((titleDescriptor){ 0x0001000248414341ULL, 0x0006,	false});
			_systemTitleList.push_back((titleDescriptor){ 0x0001000248414650ULL, 0x0007,	false});
			_systemTitleList.push_back((titleDescriptor){ 0x0001000248414750ULL, 0x0007,	false});
			break;
		case CONF_REGION_KR:
			_systemTitleList.push_back((titleDescriptor){ 0x0001000248414141ULL, 0x0002,	false});
			_systemTitleList.push_back((titleDescriptor){ 0x000100024841424BULL, 0x0012,	false});
			_systemTitleList.push_back((titleDescriptor){ 0x0001000248414341ULL, 0x0006,	false});
			_systemTitleList.push_back((titleDescriptor){ 0x0001000248414641ULL, 0x0007,	false});
			_systemTitleList.push_back((titleDescriptor){ 0x0001000248414741ULL, 0x0007,	false});
			break;
	}	
	
	_systemTitleList.push_back((titleDescriptor){ 0x00000001000000feULL, 0x0104,	true}); //bootmi IOS
	_systemTitleList.push_back((titleDescriptor){ 0x00000001000000deULL, 0xff00,	true}); // we put the stubs at the end to avoid any problems
	_systemTitleList.push_back((titleDescriptor){ 0x00000001000000dfULL, 0xff00,	true}); // hermes cioses
	_systemTitleList.push_back((titleDescriptor){ 0x00000001000000faULL, 0xff00,	true}); // this remove the 250
	_systemTitleList.push_back((titleDescriptor){ 0x00000001000000f9ULL, 0xff00,	true}); // the 249 at the end
}

void Config::CreateUpdateList(bool uninstall)
{
	if(uninstall)
	{
		for(vector<titleDescriptor>::iterator ios = Instance()._systemTitleList.begin(); ios != Instance()._systemTitleList.end(); ios++)
		{
			if(!IS_IOS(ios->title) && Title::IsInstalled(ios->title) && Title::GetInstalledTitleVersion(ios->title) >= ios->revision)
				continue;
				
			Instance()._updateList.push_back(*ios);
		}
		
		Instance()._updateSystem = true;
		return;
	}
	
	for(vector<titleDescriptor>::iterator ios = Instance()._systemTitleList.begin(); ios != Instance()._systemTitleList.end(); ios++)
	{
		bool addIt = true;
		
		if(ios->onlyOnUninstall)
			continue;
			
		if(Instance()._installCorp)
		  for(vector<ciosDesc>::iterator corp = Instance()._corp.begin(); corp != Instance()._corp.end(); corp++)
			if(0x100000000ULL + corp->destId == ios->title)
			{
				addIt = false;
				break;
			}
			
		if(!IS_IOS(ios->title) && Title::IsInstalled(ios->title) && Title::GetInstalledTitleVersion(ios->title) >= ios->revision)
		  addIt=false;

		if(addIt)
			Instance()._updateList.push_back(*ios);
	}
}

Config& Config::Instance()
{
	static Config c;
	return c;
}

bool Config::HasNetwork()
{
	return Instance()._hasNetwork;
}

u32 Config::DowngradeIos()
{
	return Instance()._downgradeIos;
}

u16 Config::DowngradeIosRevision()
{
	return Instance()._downgradeIosRevision;
}

u32 Config::TruchaIOS()
{
	return Instance()._truchaIos;
}

u32 Config::CiosSlot()
{
	return Instance()._ciosSlot;
}

u16 Config::CiosRevision()
{
	return Instance()._ciosRevision;
}

std::vector<ciosDesc>& Config::CorpConfiguration()
{
	return Instance()._corp;
}

std::vector<titleDescriptor>& Config::UpdateList()
{
	return Instance()._updateList;
}

bool Config::RestoreTrucha()
{
	return Instance()._restoreTrucha;
}
void Config::RestoreTrucha(const bool& value)
{
	Instance()._restoreTrucha = value;
}

bool Config::InstallCios()
{
	return Instance()._installCios;
}
void Config::InstallCios(const bool& value)
{
	Instance()._installCios = value;
}

bool Config::InstallCorp()
{
	return Instance()._installCorp;
}
void Config::InstallCorp(const bool& value)
{
	Instance()._installCorp = value;
}

bool Config::UpdateSystem()
{
	return Instance()._updateSystem;
}
void Config::UpdateSystem(const bool& value)
{
	Instance()._updateSystem = value;
}

bool Config::InstallGX()
{
	return Instance()._installGX;
}

void Config::InstallGX(const bool& value)
{
	Instance()._installGX = value;
}