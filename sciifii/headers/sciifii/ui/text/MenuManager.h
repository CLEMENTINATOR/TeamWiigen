#ifndef _MENU_MANAGER_H_
#define _MENU_MANAGER_H_

#include <map>
#include <vector>
#include <Libwiisys/Object.h>
#include "DynamicMenu.h"
#include <vector>

class MenuManager : public Libwiisys::Object
{
  private:
    std::map<std::string, DynamicMenu*> _menus;
    std::vector<std::string> _menuPath;
    MenuManager();
    void Initialyze(TiXmlElement* node);
    bool ExecuteSciifii();
    std::string _startId;
  public:
    ~MenuManager();
    void DisplayMenu();
    static MenuManager& Instance(TiXmlElement* node = NULL);
};

#endif
