#include <sciifii/ui/text/MenuItems/MenuItemFactory.h>
#include <Libwiisys/String/UtilString.h>
#include <Libwiisys/Exceptions/Exception.h>
#include <string>

#include <sciifii/ui/text/MenuItems/ExitMenuItem.h>
#include <sciifii/ui/text/MenuItems/MenuItem.h>
#include <sciifii/ui/text/MenuItems/ModeMenuItem.h>
#include <sciifii/ui/text/MenuItems/NavigationMenuItem.h>
#include <sciifii/ui/text/MenuItems/SeparatorMenuItem.h>
#include <sciifii/ui/text/MenuItems/StartMenuItem.h>
#include <sciifii/ui/text/MenuItems/SwitchMenuItem.h>
#include <sciifii/ui/text/MenuItems/MultiSwitchMenuItem.h>
#include <sciifii/ui/text/MenuItems/MenuItemFactory.h>
#include <sciifii/ui/text/MenuItems/PreviousMenuItem.h>

using namespace std;
using namespace Libwiisys::String;
using namespace Libwiisys::Exceptions;

MenuItem* MenuItemFactory::CreateItem(TiXmlElement* node)
{
  string nodeValue = UtilString::ToStr(node->Value(), "");

  if (nodeValue == "exitMenuItem")
  {
    return new ExitMenuItem(node);
  }
  else if (nodeValue == "navigationMenuItem")
  {
    return new NavigationMenuItem(node);
  }
  else if (nodeValue == "modeMenuItem")
  {
    return new ModeMenuItem(node);
  }
  else if (nodeValue == "switchMenuItem")
  {
    return new SwitchMenuItem(node);
  }
  else if (nodeValue == "separatorMenuItem")
  {
    return new SeparatorMenuItem(node);
  }
  else if (nodeValue == "startMenuItem")
  {
    return new StartMenuItem(node);
  }
  else if (nodeValue == "multiSwitchMenuItem")
  {
    return new MultiSwitchMenuItem(node);
  }
  else if (nodeValue == "previousMenuItem")
  {
    return new PreviousMenuItem(node);
  }
  else
    throw Exception("Incorrect node : " + nodeValue);

}
