#ifndef _EXIT_MENU_ITEM_H_
#define _EXIT_MENU_ITEM_H_

#include <string>
#include <Libwiisys/Serialization/Xml.h>
#include "NavigationMenuItem.h"

class ExitMenuItem : public NavigationMenuItem
{
  public:
    ExitMenuItem(TiXmlElement* node);
    virtual void ButtonPressed(u32 button);
};

#endif
