#ifndef _G_NAVIGATION_MENU_ITEM_H_
#define _G_NAVIGATION_MENU_ITEM_H_

#include <string>
#include <Libwiisys/Serialization/Xml.h>
#include <Libwui/Component/Button.hpp>
#include "IMenuItem.h"

class GNavigationMenuItem : public IMenuItem, public Libwui::Component::Button
{
  protected:
    std::string _navigationMenuId;
    bool _validate;

  public:
    GNavigationMenuItem(TiXmlElement* node);
    virtual void OnClick(Libwui::Device::PadController &c);
};

#endif
