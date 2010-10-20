#ifndef _G_NAVIGATION_MENU_ITEM_H_
#define _G_NAVIGATION_MENU_ITEM_H_

#include <string>
#include <Libwiisys/Serialization/Xml.h>
#include <Libwui/Component/Button.hpp>
#include "GMenuItem.h"

class GNavigationMenuItem : public GMenuItem
{
  protected:
	Libwui::Component::Button _btn;
    std::string _navigationMenuId;
    bool _validate;

    void ManageClick(Libwiisys::Object* sender, Libwui::Events::CursorEventArgs* args);

  public:
    GNavigationMenuItem(TiXmlElement* node);
    void InitializeComponents();
};

#endif
