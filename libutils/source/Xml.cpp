#include <Xml.h>
#include <fs/File.h>

#include <exception/Exception.h>
#include <fs/Device.h>
#include <sstream>

using namespace std;
string Xml::CharToStr(const char* value)
{
  if (value)return string(value);

  else return "";
}


u64 Xml::CharToU64(const char* val, NumberRepresentation rep)
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

u32 Xml::CharToU32(const char* val, NumberRepresentation rep)
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

u16 Xml::CharToU16(const char* val, NumberRepresentation rep)
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

s32 Xml::CharToS32(const char* val, NumberRepresentation rep)
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

bool Xml::CharToBool(const char* val)
{
  if (val==NULL)
    throw Exception("Cannot parse NULL value to bool", -1);
  if (!strcmp(val,"true"))
    return true;
  else if (!strcmp(val,"false"))
    return false;
  else
    throw Exception("Error parsing bool value", -1);
}

u64 Xml::CharToU64(const char* val, u64 defaultval, NumberRepresentation rep)
{
  if (val==NULL) return defaultval;

  stringstream str(val);
  u64 returnValue;

  if (rep == nr_hex)
    str >> hex;

  str >> returnValue;
  return returnValue;

}

u32 Xml::CharToU32(const char* val, u32 defaultval,NumberRepresentation rep)
{
  if (val==NULL) return defaultval;

  stringstream str(val);
  u32 returnValue;

  if (rep == nr_hex)
    str >> hex;

  str >> returnValue;
  return returnValue;
}

u16 Xml::CharToU16(const char* val,  u16 defaultval,NumberRepresentation rep)
{
  if (val==NULL) return defaultval;
  stringstream str(val);
  u16 returnValue;

  if (rep == nr_hex)
    str >> hex;

  str >> returnValue;
  return returnValue;
}

s32 Xml::CharToS32(const char* val,  s32 defaultval,NumberRepresentation rep)
{
  if (val==NULL) return defaultval;
  stringstream str(val);
  s32 returnValue;

  if (rep == nr_hex)
    str >> hex;

  str >> returnValue;
  return returnValue;
}

bool Xml::CharToBool(const char* val,bool defaultval)
{
  if (val==NULL) return defaultval;
  string value=CharToStr(val);
  if (value == "true")
    return true;
  else if (value == "false")
    return false;
  else
    throw Exception("Error parsing bool value", -1);
}

TiXmlDocument& Xml::Load(const string &file)
{
  Device::Mount(file);
  if (! File::Exists(file))
    throw Exception("The specified xml file not found !", -1);
  TiXmlDocument* doc = new TiXmlDocument(file.c_str());
  doc->LoadFile();
  Device::UnMount(file);
  return *doc;
}
