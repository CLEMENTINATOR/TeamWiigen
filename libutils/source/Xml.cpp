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
u64 Xml::StrToU64(const string& val, NumberRepresentation rep)
{
  stringstream str(val);
  u64 returnValue;

  if (rep == nr_hex)
    str >> hex;

  str >> returnValue;
  return returnValue;
}

u32 Xml::StrToU32(const string& val, NumberRepresentation rep)
{
  stringstream str(val);
  u32 returnValue;

  if (rep == nr_hex)
    str >> hex;

  str >> returnValue;
  return returnValue;
}

u16 Xml::StrToU16(const string& val, NumberRepresentation rep)
{
  stringstream str(val);
  u16 returnValue;

  if (rep == nr_hex)
    str >> hex;

  str >> returnValue;
  return returnValue;
}

s32 Xml::StrToS32(const string& val, NumberRepresentation rep)
{
  stringstream str(val);
  s32 returnValue;

  if (rep == nr_hex)
    str >> hex;

  str >> returnValue;
  return returnValue;
}

bool Xml::StrToBool(const string& val)
{
  if (val == "true")
    return true;
  else if (val == "false")
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
