#include <sstream>
#include <libwiisys/String/UtilString.h>
#include <libwiisys/String/NumberRepresentation.h>
#include <libwiisys/Exceptions/Exception.h>

using namespace std;
using namespace Libwiisys::String;
using namespace Libwiisys::Exceptions;

string UtilString::ToStr(const char* value)
{
  if (!value)
    throw Exception("Cannot parse NULL value to string");

  return string(value);
}

string UtilString::ToStr(const char* value, const string& defaultVal)
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
  if (val == NULL)
    throw Exception("Cannot parse NULL value to u64");

  stringstream str(val);
  u64 returnValue;

  if (rep == nr_hex)
    str >> hex;

  str >> returnValue;
  return returnValue;
}

u32 UtilString::ToU32(const char* val, u32 defaultval, NumberRepresentation rep)
{
  if (val == NULL)
    return defaultval;

  stringstream str(val);
  u32 returnValue;

  if (rep == nr_hex)
    str >> hex;

  str >> returnValue;
  return returnValue;
}

u32 UtilString::ToU32(const char* val, NumberRepresentation rep)
{
  if (val == NULL)
    throw Exception("Cannot parse NULL value to u32");
  stringstream str(val);
  u32 returnValue;

  if (rep == nr_hex)
    str >> hex;

  str >> returnValue;
  return returnValue;
}

u16 UtilString::ToU16(const char* val, u16 defaultval, NumberRepresentation rep)
{
  if (val == NULL)
    return defaultval;
  stringstream str(val);
  u16 returnValue;

  if (rep == nr_hex)
    str >> hex;

  str >> returnValue;
  return returnValue;
}

u16 UtilString::ToU16(const char* val, NumberRepresentation rep)
{
  if (val == NULL)
    throw Exception("Cannot parse NULL value to u16");
  stringstream str(val);
  u16 returnValue;

  if (rep == nr_hex)
    str >> hex;

  str >> returnValue;
  return returnValue;
}

u8 UtilString::ToU8(const char* val, u8 defaultval, NumberRepresentation rep)
{
  if (val == NULL)
    return defaultval;

  stringstream str(val);
  u16 returnValue;

  if (rep == nr_hex)
    str >> hex;

  str >> returnValue;

  return (u8) returnValue;
}

u8 UtilString::ToU8(const char* val, NumberRepresentation rep)
{
  if (val == NULL)
    throw Exception("Cannot parse NULL value to u8");

  stringstream str(val);
  u16 returnValue;

  if (rep == nr_hex)
    str >> hex;

  str >> returnValue;
  return (u8) returnValue;
}

s32 UtilString::ToS32(const char* val, NumberRepresentation rep)
{
  if (val == NULL)
    throw Exception("Cannot parse NULL value to s32");
  stringstream str(val);
  s32 returnValue;

  if (rep == nr_hex)
    str >> hex;

  str >> returnValue;
  return returnValue;
}

s32 UtilString::ToS32(const char* val, s32 defaultval, NumberRepresentation rep)
{
  if (val == NULL)
    return defaultval;
  stringstream str(val);
  s32 returnValue;

  if (rep == nr_hex)
    str >> hex;

  str >> returnValue;
  return returnValue;
}

bool UtilString::ToBool(const char* val)
{
  if (val == NULL)
    throw Exception("Cannot parse NULL value to bool");

  string value(val);

  if (value == "true")
    return true;
  else if (value == "false")
    return false;
  else
    throw Exception("Error parsing bool value");
}

bool UtilString::ToBool(const char* val, bool defaultval)
{
  if (val == NULL)
    return defaultval;
  string value = ToStr(val);
  if (value == "true")
    return true;
  else if (value == "false")
    return false;
  else
    throw Exception("Error parsing bool value");
}

vector<string> UtilString::Split(const string& str, const char splitCaracter,
                                 bool removeEmpty)
{
  vector < string > voptions;
  string modeOptions = str;
  u32 position = 0;

  while ((position = modeOptions.find_first_of(splitCaracter))
         != string::npos)
  {
    string item = modeOptions.substr(0, position);
    if (!removeEmpty || item != "")
      voptions.push_back(item);
    modeOptions = modeOptions.erase(0, position + 1);
  }

  if (!removeEmpty || modeOptions != "")
    voptions.push_back(modeOptions);

  return voptions;
}

string UtilString::Replace(const string& source, const string& pattern,
                           const string& value)
{
  string temp = source;
  size_t found;

  while ((found = temp.find(pattern)) != string::npos)
  {
    temp = temp.replace(found, pattern.length(), value);
  }

  return temp;
}

wstring UtilString::StrToWstr(const string& str)
{
  wstring wstr;
  wstr.assign(str.begin(), str.end());
  return wstr;
}

string UtilString::WstrToStr(const wstring& wstr)
{
  string str;
  str.assign(wstr.begin(), wstr.end());
  return str;
}


std::string UtilString::GetType()
{
  return "Libwiisys::String::UtilString,"+Object::GetType();
}
