#include <sciifii/ui/graphic/MenuItems/GMenuItemFactory.h>

#include "sciifii/ui/graphic/MenuItems/GNavigationMenuItem.h"
#include "sciifii/ui/graphic/MenuItems/GMenuItemFactory.h"
#include "sciifii/ui/graphic/MenuItems/GModeMenuItem.h"
#include "sciifii/ui/graphic/MenuItems/GExitMenuItem.h"
#include "sciifii/ui/graphic/MenuItems/GSeparatorMenuItem.h"
#include "sciifii/ui/graphic/MenuItems/GSwitchMenuItem.h"
#include "sciifii/ui/graphic/MenuItems/GMenuItem.h"

using namespace std;
using namespace Libwiisys::String;
using namespace Libwiisys::Exceptions;

GMenuItem* GMenuItemFactory::CreateItem(TiXmlElement* node)
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
	else if (nodeValue == "separatorMenuItem")
  {
    return new GSeparatorMenuItem(node);
  }
	else if (nodeValue == "switchMenuItem")
  {
    return new GSwitchMenuItem(node);
  }
  else
    throw Exception("Incorrect node : " + nodeValue);
}
