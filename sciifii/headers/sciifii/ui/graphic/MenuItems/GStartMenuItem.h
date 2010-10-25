#ifndef _G_START_MENU_ITEM_H_
#define _G_START_MENU_ITEM_H_

#include <string>
#include <Libwiisys/Serialization/Xml.h>
#include <Libwui/Component/Button.hpp>
#include "GMenuItem.h"

class GStartMenuItem : public GMenuItem
{
  protected:
		Libwui::Component::Button _btn;
    bool _validate;

    void ManageClick(Libwiisys::Object* sender, Libwui::Events::CursorEventArgs* args);

  public:
    GStartMenuItem(TiXmlElement* node);
    void InitializeComponents();
};

#endif
