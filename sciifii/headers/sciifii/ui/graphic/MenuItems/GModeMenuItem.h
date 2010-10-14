#ifndef _G_MODE_MENU_ITEM_H_
#define _G_MODE_MENU_ITEM_H_

#include <string>
#include <Libwiisys/Serialization/Xml.h>
#include <Libwui/Component/Button.hpp>
#include "IMenuItem.h"

class GModeMenuItem : public IMenuItem, public Libwui::Component::Button
{
  protected:
    std::string _navigationMenuId;
		std::vector<std::string> _switches;

  public:
    GModeMenuItem(TiXmlElement* node);
    virtual void OnClick(Libwui::Device::PadController &c);
};

#endif
