
using namespace std;
using namespace Libwiisys::String;
using namespace Libwiisys::Exceptions;

#include <Sciifii.h>

IMenuItem* GMenuItemFactory::CreateItem(TiXmlElement* node)
{
	string nodeValue = UtilString::ToStr(node->Value(), "");

		if (nodeValue == "exitMenuItem")
		{
			return new GExitMenuItem(node);
		}
		else if (nodeValue == "navigationMenuItem")
		{
			return new GNavigationMenuItem(node);
		}
		else if (nodeValue == "modeMenuItem")
		{
			return new GModeMenuItem(node);
		}
		else
			throw Exception("Incorrect node : " + nodeValue);
}
