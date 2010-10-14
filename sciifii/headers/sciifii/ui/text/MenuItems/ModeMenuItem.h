#ifndef _MODE_MENU_ITEM_H_
#define _MODE_MENU_ITEM_H_

#include <string>
#include <vector>
#include <Libwiisys/Serialization/Xml.h>
#include "StartMenuItem.h"

class ModeMenuItem : public StartMenuItem
{
  private:
    std::vector<std::string> _switches;

  public:
    ModeMenuItem(TiXmlElement* node);
    virtual void ButtonPressed(u32 button);
};

#endif
