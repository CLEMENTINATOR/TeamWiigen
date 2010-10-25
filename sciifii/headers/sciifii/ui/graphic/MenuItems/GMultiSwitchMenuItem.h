#ifndef G_MULTISWITCH_MENU_ITEM_H_
#define G_MULTISWITCH_MENU_ITEM_H_

#include <string>
#include <vector>
#include <Libwiisys/Serialization/Xml.h>
#include "MenuItem.h"

class GMultiSwitchMenuItem : public MenuItem
{
  protected:

    std::vector<Switch> _multiSwitches;
    u32 _selectedIndex;
    u32 _lastIndex;
    bool _allowActivation;
    bool _activated;
    bool _lastActivated;
    std::string _switchName;

  public:
    GMultiSwitchMenuItem(TiXmlElement* node);
    virtual void Validate();
    virtual void Cancel();
};

#endif
