#include <sciifii/ui/text/MenuItems/PreviousMenuItem.h>

PreviousMenuItem::PreviousMenuItem(TiXmlElement* node) : NavigationMenuItem(node)
{
  _navigationMenuId = "..";
}

void PreviousMenuItem::ButtonPressed(u32 button)
{
  NavigationMenuItem::ButtonPressed(button);
}
