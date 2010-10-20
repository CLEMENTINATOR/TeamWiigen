#ifndef _G_EXIT_MENU_ITEM_H_
#define _G_EXIT_MENU_ITEM_H_

#include <string>
#include <Libwiisys/Serialization/Xml.h>
#include <Libwui/Component/Button.hpp>
#include "GMenuItem.h"

class GExitMenuItem : public GMenuItem
{
  private:
	Libwui::Component::Button _btn;
	void ManageClick(Libwiisys::Object* sender, Libwui::Events::CursorEventArgs* args);

  public:
    GExitMenuItem(TiXmlElement* node);
    void InitializeComponents();
};

#endif
