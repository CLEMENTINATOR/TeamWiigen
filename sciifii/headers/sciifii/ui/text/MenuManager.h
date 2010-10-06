#ifndef _MENU_MANAGER_H_
#define _MENU_MANAGER_H_

#include <map>
#include <libwiisys.h>
#include "DynamicMenu.h"

class MenuManager : public Libwiisys::Object
{
private:
	std::map<std::string, DynamicMenu*> _menus;
	MenuManager();
	void Initialyze(TiXmlElement* node);
	
public:
	~MenuManager();
	void DisplayMenu();
	bool ExecuteSciifii();
	
	static MenuManager& Instance(TiXmlElement* node = NULL);
};

#endif