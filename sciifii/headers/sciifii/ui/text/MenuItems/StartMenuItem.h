#ifndef _START_MENU_ITEM_H_
#define _START_MENU_ITEM_H_

#include <string>
#include <Libwiisys/Serialization/Xml.h>
#include "NavigationMenuItem.h"

class StartMenuItem : public NavigationMenuItem
{
  public:
    StartMenuItem(TiXmlElement* node);
    virtual void ButtonPressed(u32 button);
};

#endif
