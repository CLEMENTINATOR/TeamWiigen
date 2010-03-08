#include <sstream>

#include <UtilString.h>
#include <exception/Exception.h>

using namespace std;

string UtilString::ToStr(const char* value)
{
  if (!value)
	throw Exception("Cannot parse NULL value to string", -1);

  return string(value);
}

string ToStr(const char* value, const string& defaultVal)
{
  if (!value)
	return defaultVal;

  return string(value);
}

u64 UtilString::ToU64(const char* val, u64 defaultval, NumberRepresentation rep)
{
  if (val == NULL) 
    return defaultval;

  stringstream str(val);
  u64 returnValue;

  if (rep == nr_hex)
    str >> hex;

  str >> returnValue;
  return returnValue;
}

u64 UtilString::ToU64(const char* val, NumberRepresentation rep)
{
  if (val==NULL)
    throw Exception("Cannot parse NULL value to u64", -1);
	
  stringstream str(val);
  u64 returnValue;

  if (rep == nr_hex)
    str >> hex;

  str >> returnValue;
  return returnValue;
}

u32 UtilString::ToU32(const char* val, u32 defaultval, NumberRepresentation rep)
{
  if (val==NULL) return defaultval;

  stringstream str(val);
  u32 returnValue;

  if (rep == nr_hex)
    str >> hex;

  str >> returnValue;
  return returnValue;
}

u32 UtilString::ToU32(const char* val, NumberRepresentation rep)
{
  if (val==NULL)
    throw Exception("Cannot parse NULL value to u32", -1);
  stringstream str(val);
  u32 returnValue;

  if (rep == nr_hex)
    str >> hex;

  str >> returnValue;
  return returnValue;
}

u16 UtilString::ToU16(const char* val, u16 defaultval, NumberRepresentation rep)
{
  if (val==NULL) return defaultval;
  stringstream str(val);
  u16 returnValue;

  if (rep == nr_hex)
    str >> hex;

  str >> returnValue;
  return returnValue;
}

u16 UtilString::ToU16(const char* val, NumberRepresentation rep)
{
  if (val==NULL)
    throw Exception("Cannot parse NULL value to u16", -1);
  stringstream str(val);
  u16 returnValue;

  if (rep == nr_hex)
    str >> hex;

  str >> returnValue;
  return returnValue;
}

u8 UtilString::ToU8(const char* val, u8 defaultval, NumberRepresentation rep)
{
  if (val==NULL) 
    return defaultval;
	
  stringstream str(val);
  u16 returnValue;

  if (rep == nr_hex)
    str >> hex;

  str >> returnValue;
  
  return (u8)returnValue;
}

u8 UtilString::ToU8(const char* val, NumberRepresentation rep)
{
  if (val==NULL)
    throw Exception("Cannot parse NULL value to u16", -1);
	
  stringstream str(val);
  u16 returnValue;

  if (rep == nr_hex)
    str >> hex;

  str >> returnValue;
  return (u8)returnValue;
}

s32 UtilString::ToS32(const char* val, NumberRepresentation rep)
{
  if (val==NULL)
    throw Exception("Cannot parse NULL value to s32", -1);
  stringstream str(val);
  s32 returnValue;

  if (rep == nr_hex)
    str >> hex;

  str >> returnValue;
  return returnValue;
}

s32 UtilString::ToS32(const char* val,  s32 defaultval,NumberRepresentation rep)
{
  if (val==NULL) return defaultval;
  stringstream str(val);
  s32 returnValue;

  if (rep == nr_hex)
    str >> hex;

  str >> returnValue;
  return returnValue;
}

bool UtilString::ToBool(const char* val)
{
  if (val==NULL)
    throw Exception("Cannot parse NULL value to bool", -1);
	
  string value(val);
  
  if (value == "true")
    return true;
  else if (value == "false")
    return false;
  else
    throw Exception("Error parsing bool value", -1);
}

bool UtilString::ToBool(const char* val,bool defaultval)
{
  if (val==NULL) return defaultval;
  string value=ToStr(val);
  if (value == "true")
    return true;
  else if (value == "false")
    return false;
  else
    throw Exception("Error parsing bool value", -1);
}

vector<string> UtilString::Split(const string& str, const char splitCaracter)
{
	vector<string> voptions;
    string modeOptions = str;
    u32 position = 0;

    while ((position = modeOptions.find_first_of(splitCaracter)) != string::npos)
    {
        voptions.push_back(modeOptions.substr(0, position));
        modeOptions = modeOptions.erase(0, position + 1);
    }

    voptions.push_back(modeOptions);

    return voptions;
}