#ifndef G_MENU_MANAGER_H_
#define G_MENU_MANAGER_H_

#include <map>
#include <string>
#include <Libwui/Control.hpp>
#include <Libwiisys/Serialization/Xml.h>
#include "GDynamicMenu.h"

class GMenuManager : public Libwui::Control
{
  private:
    std::map<std::string, GDynamicMenu*> _menus;
    std::vector<std::string> _menuPath;
    GMenuManager();
    void Initialyze(TiXmlElement* node);
    std::string _startId;
		std::string _currentMenu;
		void Menu_NavigateRequested(Libwiisys::Object* sender, NavigateEventArgs* args);
		
	protected:
		void EnsureItems();
		
  public:
		static GMenuManager& Instance(TiXmlElement* node = NULL);
    ~GMenuManager();
		
		void InitializeComponents();
};

#endif
