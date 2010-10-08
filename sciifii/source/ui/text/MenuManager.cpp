#include <Sciifii.h>

using namespace std;
using namespace Libwiisys::String;
using namespace Libwiisys::Exceptions;
using namespace Libwiisys::Logging;

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

	 _startId = UtilString::ToStr(node->Attribute("start"),"");
	if(_startId=="")
		throw Exception("No start menu specified !");
	_menuPath.push_back(_startId);

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
	if(_menus.find(_startId)==_menus.end())
		throw Exception("start menu doesn't exist : "+_startId);
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
	string activeMenu = _startId;

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
		{
			if(result.MenuId == "..")
			{
				if(_menuPath.size() == 1)
					throw Exception("There isn't previous menu...");
				_menuPath.pop_back();
				activeMenu = _menuPath.back();
			}
			else
			{
				_menuPath.push_back(result.MenuId);
				activeMenu = result.MenuId;
			}
		}
	}
}

bool MenuManager::ExecuteSciifii()
{
	try
	{
		Config::ValidateOptions();
		Disclaimer::Show();
		VPAD_Shutdown();

		Sciifii sci;
		if (sci.Prepare())
		{
				sci.Execute();
				cout << "Installation done! Press A to exit.";
		}
		else
		{
			Log::WriteLog(Log_Error,Sciifii::LastStepMessage());
			throw Exception("An error occured during prepare.");
		}

		return true;
	}
	catch(AbortException& ex)
	{
		return false;
	}
}
