#include <libwiisys.h>
#include <sstream>

using namespace std;
using namespace Libwiisys::Serialization;
using namespace Libwiisys::IO;
using namespace Libwiisys::Exceptions;

TiXmlDocument& Xml::Load(const std::string &file) {
	Device::Mount(file);
	if (!File::Exists(file))
		throw Exception("The specified xml file not found !");
	TiXmlDocument* doc = new TiXmlDocument(file.c_str());
	doc->LoadFile();
	Device::UnMount(file);
	return *doc;
}

