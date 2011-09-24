#ifndef _DYNAMIC_MENU_H_
#define _DYNAMIC_MENU_H_

#include <ogcsys.h>
#include <string>
#include <vector>
#include <Libwiisys/Object.h>
#include "MenuBase.h"
#include "MenuItems/MenuItem.h"
#include "../Events/NavigateEventArgs.h"
#include "../Events/SwitchEventArgs.h"

class DynamicMenu : public MenuBase
{
  private:
    std::vector<MenuItem*> items;
    u32 selectIndex;
    NavigateEventArgs nav;
	std::string _message;
	std::string _title;
    void Display();
    void SwitchSelectionChanged(Libwiisys::Object* sender, SwitchEventArgs* args);
    void NavigateRequested(Libwiisys::Object* sender, NavigateEventArgs* args);

  public:
    std::string MenuId;
    DynamicMenu(TiXmlElement* node);
    void Reset();
    ~DynamicMenu();
    NavigateEventArgs Show();
};

#endif
