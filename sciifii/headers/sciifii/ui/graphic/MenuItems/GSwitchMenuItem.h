#ifndef _G_SWITCH_MENU_ITEM_H_
#define _G_SWITCH_MENU_ITEM_H_

#include <string>
#include <Libwiisys/Serialization/Xml.h>
#include <Libwui/Component/Checkbox.hpp>
#include "GMenuItem.h"

class GSwitchMenuItem : public GMenuItem
{
  protected:
    bool _lastSwitchOn;
    std::string _switchName;
		Libwui::Component::Checkbox _cbx;
		
  public:
    GSwitchMenuItem(TiXmlElement* node);
		void InitializeComponents();
    virtual void Validate();
    virtual void Cancel();
};

#endif
