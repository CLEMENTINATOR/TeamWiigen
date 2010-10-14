#ifndef _NAVIGATION_MENU_ITEM_H_
#define _NAVIGATION_MENU_ITEM_H_

#include <string>
#include <Libwiisys/Serialization/Xml.h>
#include "MenuItem.h"

class NavigationMenuItem : public MenuItem
{
  protected:
    std::string _navigationMenuId;
    bool _validate;

  public:
    NavigationMenuItem(TiXmlElement* node);
    virtual void ButtonPressed(u32 button);
};

#endif
