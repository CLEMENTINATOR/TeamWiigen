#ifndef G_MENU_MANAGER_H_
#define G_MENU_MANAGER_H_

#include <map>
#include <string>
#include <Libwui/Component/Form.hpp>
#include <Libwui/Component/MessageBox.hpp>
#include <Libwiisys/Serialization/Xml.h>
#include "GDynamicMenu.h"
#include "GThemeDdl.h"

class GMenuManager : public Libwui::Component::Form
{
  private:
    std::map<std::string, GDynamicMenu*> _menus;
    std::vector<std::string> _menuPath;
		std::string _startId;
		std::string _currentMenu;
		
		Libwui::Component::Button btnExit;
		Libwui::Component::MessageBox mb;
		GThemeDdl _themeDdl;
		
    GMenuManager();
    void Initialyze(TiXmlElement* node);
		void Menu_NavigateRequested(Libwiisys::Object* sender, NavigateEventArgs* args);
		bool ExecuteSciifii();
		
		void Exit(Libwiisys::Object* sender, Libwui::Events::CursorEventArgs* args);
		
	protected:
		void EnsureItems();
		
  public:
		static GMenuManager& Instance(TiXmlElement* node = NULL);
    ~GMenuManager();
		
		void InitializeComponents();
};

#endif
