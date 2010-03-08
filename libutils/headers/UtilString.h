#ifndef _UTILS_STRING_H_
#define _UTILS_STRING_H_

#include <string>
#include <vector>

#include <gctypes.h>
#include "Object.h"

typedef enum
{
  nr_normal,
  nr_hex,
} NumberRepresentation;

class UtilString : public Object
{
public:
	static u64 ToU64(const char* val, NumberRepresentation rep = nr_normal);
	static u64 ToU64(const char* val, u64 defaultval, NumberRepresentation rep = nr_normal);
	
	static u32 ToU32(const char* val, NumberRepresentation rep = nr_normal);
    static u32 ToU32(const char* val, u32 defaultval, NumberRepresentation rep = nr_normal);
	
	static u16 ToU16(const char* val, NumberRepresentation rep = nr_normal);
    static u16 ToU16(const char* val, u16 defaultval, NumberRepresentation rep = nr_normal);
	
	static u8 ToU8(const char* val, NumberRepresentation rep = nr_normal);
    static u8 ToU8(const char* val, u8 defaultval, NumberRepresentation rep = nr_normal);
	
	static s32 ToS32(const char* val, NumberRepresentation rep = nr_normal);
    static s32 ToS32(const char* val, s32 defaultval, NumberRepresentation rep = nr_normal);
	
    static bool ToBool(const char* val);
    static bool ToBool(const char* val, bool defaultval);

    static std::string ToStr(const char* value);
	static std::string ToStr(const char* value, const std::string& defaultVal);
	
	static std::vector<std::string> Split(const std::string& str, const char split);
};

#endif