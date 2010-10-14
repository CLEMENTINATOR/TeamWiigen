#ifndef GDYNAMICMENU_H_
#define GDYNAMICMENU_H_

#include <string>
#include <vector>
#include "MenuItems/IMenuItem.h"
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
	std::string MenuId;
	std::vector<IMenuItem*> items;
	u32 _nbSkip;

	Libwui::Component::Button _btnDown;
	Libwui::Component::Button _btnUp;

	void Item_SwitchSelectionChanged(Libwiisys::Object* sender, SwitchEventArgs* args);
	void Item_NavigateRequested(Libwiisys::Object* sender, NavigateEventArgs* args);
	void btnUp_Clicked(Object* sender, Libwui::Events::CursorEventArgs* args);
	void btnDown_Clicked(Object* sender, Libwui::Events::CursorEventArgs* args);
	void EnsureItems();
  public:
	GDynamicMenu(TiXmlElement* node);
	~GDynamicMenu();

	virtual void InitializeComponents();

	NavigateEvent NavigateRequested;
};

#endif
