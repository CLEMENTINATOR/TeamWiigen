#include "Config.h"
#include <libutils/com/NetworkRequest.h>

Config::Config()
: _hasNetwork(false),
  _downgradeIos(15),
  _downgradeIosRevision(257),
  _truchaIos(16),
  _corp()
{
	try
	{
		NetworkRequest::GetIp();
		_hasNetwork = true;
	}
	catch(...)
	{}

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

std::vector<ciosDesc>& Config::CorpConfiguration()
{
	return Instance()._corp;
}
