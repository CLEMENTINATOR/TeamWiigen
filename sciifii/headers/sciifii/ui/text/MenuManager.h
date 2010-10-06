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
	bool ExecuteSciifii();
	
public:
	~MenuManager();
	void DisplayMenu();
	static MenuManager& Instance(TiXmlElement* node = NULL);
};

#endif