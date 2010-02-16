#ifndef _UTILS_XML_H
#define _UTILS_XML_H

#include <string>
#include <tinyxml.h>
#include <string>
#include <gctypes.h>

class Xml
{
public:
	static TiXmlDocument& Load(const std::string &file);
	static u64 StrToU64(const std::string& val);
	static u32 StrToU32(const std::string& val);
	static u16 StrToU16(const std::string& val);
	static u8 StrToU8(const std::string& val);
	static s32 StrToS32(const std::string& val);
	static bool StrToBool(const std::string& val);
};

#endif
