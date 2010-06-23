#include <Xml.h>
#include <fs/File.h>

#include <exception/Exception.h>
#include <fs/Device.h>
#include <sstream>

using namespace std;
using namespace Libwiisys::Serialization;

/**
*\brief Load the xml specified by path
*\param file The file path
*\return The TiXmlDocument loaded
*/
TiXmlDocument& Xml::Load(const std::string &file)
{
  Device::Mount(file);
  if (! File::Exists(file))
    throw Exception("The specified xml file not found !", -1);
  TiXmlDocument* doc = new TiXmlDocument(file.c_str());
  doc->LoadFile();
  Device::UnMount(file);
  return *doc;
}