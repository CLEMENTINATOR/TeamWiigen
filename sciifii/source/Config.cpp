#include "Config.h"
#include <libutils/com/NetworkRequest.h>

using namespace std;

Config::Config()
: _hasNetwork(false),
  _downgradeIos(15),
  _downgradeIosRevision(257),
  _truchaIos(36),
  _corp(),
  _updateList(),
  _partialUpdateList()
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
	
	_updateList.push_back((titleDescriptor){ 0x0000000100000004ULL, 0xff00});
	_updateList.push_back((titleDescriptor){ 0x0000000100000009ULL, 0x030a});
	_updateList.push_back((titleDescriptor){ 0x000000010000000aULL, 0x0300});
	_updateList.push_back((titleDescriptor){ 0x000000010000000bULL, 0x0100});
	_updateList.push_back((titleDescriptor){ 0x000000010000000cULL, 0x010d});
	_updateList.push_back((titleDescriptor){ 0x000000010000000dULL, 0x0111});
	_updateList.push_back((titleDescriptor){ 0x000000010000000eULL, 0x0208});
	_updateList.push_back((titleDescriptor){ 0x000000010000000fULL, 0x020b});
	_updateList.push_back((titleDescriptor){ 0x0000000100000010ULL, 0x0200});
	_updateList.push_back((titleDescriptor){ 0x0000000100000011ULL, 0x0307});
	_updateList.push_back((titleDescriptor){ 0x0000000100000014ULL, 0x0100});
	_updateList.push_back((titleDescriptor){ 0x0000000100000015ULL, 0x030e});
	_updateList.push_back((titleDescriptor){ 0x0000000100000016ULL, 0x040d});
	_updateList.push_back((titleDescriptor){ 0x000000010000001cULL, 0x060e});
	_updateList.push_back((titleDescriptor){ 0x000000010000001eULL, 0x0b00});
	_updateList.push_back((titleDescriptor){ 0x000000010000001fULL, 0x0d15});
	_updateList.push_back((titleDescriptor){ 0x0000000100000021ULL, 0x0c13});
	_updateList.push_back((titleDescriptor){ 0x0000000100000022ULL, 0x0d14});
	_updateList.push_back((titleDescriptor){ 0x0000000100000023ULL, 0x0d15});
	_updateList.push_back((titleDescriptor){ 0x0000000100000024ULL, 0x0d17});
	_updateList.push_back((titleDescriptor){ 0x0000000100000025ULL, 0x0f1d});
	_updateList.push_back((titleDescriptor){ 0x0000000100000026ULL, 0x0f1b});
	_updateList.push_back((titleDescriptor){ 0x0000000100000032ULL, 0x1400});
	_updateList.push_back((titleDescriptor){ 0x0000000100000033ULL, 0x1300});
	_updateList.push_back((titleDescriptor){ 0x0000000100000035ULL, 0x151e});
	_updateList.push_back((titleDescriptor){ 0x0000000100000037ULL, 0x151e});
	_updateList.push_back((titleDescriptor){ 0x0000000100000038ULL, 0x151d});
	_updateList.push_back((titleDescriptor){ 0x0000000100000039ULL, 0x161d});
	_updateList.push_back((titleDescriptor){ 0x000000010000003dULL, 0x151d});
	_updateList.push_back((titleDescriptor){ 0x0000000100000046ULL, 0x1a1f});
	_updateList.push_back((titleDescriptor){ 0x0000000100000002ULL, 0x01e2}); //we put the system menu after ios70 loading to avoid bricks if ios70 isn't ok
	_updateList.push_back((titleDescriptor){ 0x000000010000003cULL, 0x1900}); //the ios60 stub is placed after the new SysMenu installation
	_updateList.push_back((titleDescriptor){ 0x00000001000000deULL, 0xff00});
	_updateList.push_back((titleDescriptor){ 0x00000001000000dfULL, 0xff00});
	_updateList.push_back((titleDescriptor){ 0x00000001000000f9ULL, 0xff00});
	_updateList.push_back((titleDescriptor){ 0x00000001000000faULL, 0xff00});
	_updateList.push_back((titleDescriptor){ 0x00000001000000feULL, 0x0104});
	_updateList.push_back((titleDescriptor){ 0x0000000100000100ULL, 0x0006});
	_updateList.push_back((titleDescriptor){ 0x0000000100000101ULL, 0x000a});
	_updateList.push_back((titleDescriptor){ 0x0001000248414141ULL, 0x0002});
	_updateList.push_back((titleDescriptor){ 0x0001000248414241ULL, 0x0012});
	_updateList.push_back((titleDescriptor){ 0x0001000248414341ULL, 0x0006});
	_updateList.push_back((titleDescriptor){ 0x0001000248414650ULL, 0x0007});
	_updateList.push_back((titleDescriptor){ 0x0001000248414750ULL, 0x0007});
	
	for(vector<titleDescriptor>::iterator ios = _updateList.begin(); ios != _updateList.end(); ios++)
	{
		bool addIt = true;
		for(vector<ciosDesc>::iterator corp = _corp.begin(); corp != _corp.end(); corp++)
			if(0x100000000ULL + corp->destId == ios->title)
			{
				addIt = false;
				break;
			}
			
		if(addIt)
			_partialUpdateList.push_back(*ios);
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

std::vector<ciosDesc>& Config::CorpConfiguration()
{
	return Instance()._corp;
}

std::vector<titleDescriptor>& Config::UpdateList()
{
	return Instance()._updateList;
}

std::vector<titleDescriptor>& Config::PartialUpdateList()
{
	return Instance()._partialUpdateList;
}
