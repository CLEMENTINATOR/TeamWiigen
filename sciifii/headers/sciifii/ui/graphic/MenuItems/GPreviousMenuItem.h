#ifndef _G_PREVIOUS_MENU_ITEM_H_
#define _G_PREVIOUS_MENU_ITEM_H_

#include <string>
#include <Libwiisys/Serialization/Xml.h>
#include <Libwui/Component/Button.hpp>
#include "GMenuItem.h"

class GPreviousMenuItem : public GMenuItem
{
  protected:
		Libwui::Component::Button _btn;
    bool _validate;

    void ManageClick(Libwiisys::Object* sender, Libwui::Events::CursorEventArgs* args);

  public:
    GPreviousMenuItem(TiXmlElement* node);
    void InitializeComponents();
};

#endif
