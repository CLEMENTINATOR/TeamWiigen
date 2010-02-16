#include <Xml.h>

#include <exception/Exception.h>
#include <fs/Device.h>
#include <sstream>

using namespace std;

u64 Xml::StrToU64(const string& val)
{
	stringstream str(val);
	u64 returnValue;
	str >> returnValue;
	return returnValue;
}

u32 Xml::StrToU32(const string& val)
{
	stringstream str(val);
	u32 returnValue;
	str >> returnValue;
	return returnValue;
}

u16 Xml::StrToU16(const string& val)
{
	stringstream str(val);
	u16 returnValue;
	str >> returnValue;
	return returnValue;
}

u8 Xml::StrToU8(const string& val)
{
	stringstream str(val);
	u8 returnValue;
	str >> returnValue;
	return returnValue;
}

s32 Xml::StrToS32(const string& val)
{
	stringstream str(val);
	s32 returnValue;
	str >> returnValue;
	return returnValue;
}

bool Xml::StrToBool(const string& val)
{
	if(val == "true")
		return true;
	else if(val == "false")
		return false;
	else
		throw Exception("Error parsing bool value", -1);
}

TiXmlDocument& Xml::Load(const string &file)
{
	Device::Mount(file);
	TiXmlDocument* doc = new TiXmlDocument(file.c_str());
	doc->LoadFile();
	Device::UnMount(file);
	return *doc;
}
