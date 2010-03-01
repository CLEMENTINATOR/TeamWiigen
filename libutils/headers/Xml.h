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
    static u64 CharToU64(const char* val, u64 defaultval, NumberRepresentation rep = nr_normal);
    static u32 CharToU32(const char* val, u32 defaultval, NumberRepresentation rep = nr_normal);
    static u16 CharToU16(const char* val, u16 defaultval, NumberRepresentation rep = nr_normal);
    static s32 CharToS32(const char* val, s32 defaultval, NumberRepresentation rep = nr_normal);
    static std::string CharToStr(const char* value);
    static bool CharToBool(const char* val,bool defaultval);

    static u64 CharToU64(const char* val,NumberRepresentation rep = nr_normal);
    static u32 CharToU32(const char* val, NumberRepresentation rep = nr_normal);
    static u16 CharToU16(const char* val,NumberRepresentation rep = nr_normal);
    static s32 CharToS32(const char* val,NumberRepresentation rep = nr_normal);
    static bool CharToBool(const char* val);
  };

#endif
