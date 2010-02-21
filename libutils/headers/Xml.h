#ifndef _UTILS_XML_H
#define _UTILS_XML_H

#include <string>
#include <tinyxml.h>
#include <string>
#include <gctypes.h>

typedef enum
{
	nr_normal,
	nr_hex,
} NumberRepresentation;

class Xml
{
public:
	static TiXmlDocument& Load(const std::string &file);
	static u64 StrToU64(const std::string& val, NumberRepresentation rep = nr_normal);
	static u32 StrToU32(const std::string& val, NumberRepresentation rep = nr_normal);
	static u16 StrToU16(const std::string& val, NumberRepresentation rep = nr_normal);
	static s32 StrToS32(const std::string& val, NumberRepresentation rep = nr_normal);
	static bool StrToBool(const std::string& val);
};

#endif
