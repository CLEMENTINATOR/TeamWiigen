#ifndef GDYNAMICMENU_H_
#define GDYNAMICMENU_H_

#include <string>
#include <vector>
#include "MenuItems/GMenuItem.h"
#include "../Events/SwitchEventArgs.h"
#include "../Events/NavigateEvent.h"
#include "../Events/NavigateEventArgs.h"
#include <Libwui/Control.hpp>
#include <Libwui/Component/Button.hpp>
#include <Libwiisys/Object.h>
#include <Libwiisys/Serialization/Xml.h>


class GDynamicMenu : public Libwui::Control
{
  private:
		std::vector<GMenuItem*> items;
		u32 _nbSkip;

		Libwui::Component::Button _btnDown;
		Libwui::Component::Button _btnUp;

		void Item_SwitchSelectionChanged(Libwiisys::Object* sender, SwitchEventArgs* args);
		void Item_NavigateRequested(Libwiisys::Object* sender, NavigateEventArgs* args);
		void btnUp_Clicked(Object* sender, Libwui::Events::CursorEventArgs* args);
		void btnDown_Clicked(Object* sender, Libwui::Events::CursorEventArgs* args);
		void EnsureItems();
	
  public:
		std::string MenuId;
		GDynamicMenu(TiXmlElement* node);
		void Reset();
		~GDynamicMenu();

		void InitializeComponents();

		NavigateEvent NavigateRequested;
};

#endif
