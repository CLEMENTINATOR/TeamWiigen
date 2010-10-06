#include <Sciifii.h>

using namespace std;
using namespace Libwiisys::String;
using namespace Libwiisys::Exceptions;

MenuManager::MenuManager()
{}

MenuManager::~MenuManager()
{
	for(map<string,DynamicMenu*>::iterator ite = _menus.begin(); ite != _menus.end(); ite++)
		delete ite->second;
}

void MenuManager::Initialyze(TiXmlElement* node)
{
	for(map<string,DynamicMenu*>::iterator ite = _menus.begin(); ite != _menus.end(); ite++)
		delete ite->second;
		
	_menus.clear();
		
	string nodeValue = UtilString::ToStr(node->Value());
	if(nodeValue != "menus")
		throw Exception("Can't create MenuManager from an other tag than menus");
		
	TiXmlElement* menu = node->FirstChildElement();
	while (menu != NULL)
	{
		if (menu->Type() != TiXmlElement::COMMENT)
		{
			DynamicMenu *dmenu = new DynamicMenu(menu);
			_menus.insert(pair<string,DynamicMenu*>(dmenu->MenuId, dmenu));
		}
		menu = menu->NextSiblingElement();
	}
}

MenuManager& MenuManager::Instance(TiXmlElement* node)
{
	static MenuManager manager;
	if(node != NULL)
		manager.Initialyze(node);
		
	return manager;
}

void MenuManager::DisplayMenu()
{
	string activeMenu = _menus.begin()->first;
	
	while(true)
	{
		NavigateEventArgs result = _menus[activeMenu]->Show();
		if(result.NavigateTo == "loader")
			break;
		else if(result.NavigateTo == "execution")
		{
			if(!ExecuteSciifii())
				break;
		}
		else if(result.NavigateTo == "menu")
			activeMenu = result.MenuId;
	}
}

bool MenuManager::ExecuteSciifii()
{
	try
	{
		return true;
	}
	catch(AbortException& ex)
	{
		return false;
	}
}