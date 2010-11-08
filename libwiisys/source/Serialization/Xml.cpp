#include <libwiisys/Serialization/Xml.h>
#include <sstream>
#include <libwiisys/IO/Device.h>
#include <libwiisys/IO/File.h>
#include <libwiisys/Exceptions/Exception.h>

using namespace std;
using namespace Libwiisys::Serialization;
using namespace Libwiisys::IO;
using namespace Libwiisys::Exceptions;

TiXmlDocument& Xml::Load(const std::string &file)
{
  if (!File::Exists(file))
    throw Exception("The specified xml file not found !");
	
	Device::Mount(file);
  TiXmlDocument* doc = new TiXmlDocument(file.c_str());
  doc->LoadFile();
  Device::UnMount(file);
	
  return *doc;
}

