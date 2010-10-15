#include <FastDelegate.h>
#include <sciifii/ui/graphic/GMenuManager.h>
#include <Libwui/Resources/Colors.h>
#include <Libwiisys/string/UtilString.h>
#include <Libwiisys/Exceptions/Exception.h>

using namespace std;
using namespace fastdelegate;
using namespace Libwiisys::String;
using namespace Libwiisys::Exceptions;
using namespace Libwui::Resources;

GMenuManager::GMenuManager()
{
	BackgroundImage("sd:/sciifii/default/advanced_screen.png");
  SetSize(640, 480);
	//44,142 à 596,377 (taille inner menu)
}

GMenuManager::~GMenuManager()
{
  for(map<string,GDynamicMenu*>::iterator ite = _menus.begin(); ite != _menus.end(); ite++)
    delete ite->second;
}

void GMenuManager::Initialyze(TiXmlElement* node)
{
  for(map<string,GDynamicMenu*>::iterator ite = _menus.begin(); ite != _menus.end(); ite++)
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
      GDynamicMenu *dmenu = new GDynamicMenu(menu);
      _menus.insert(pair<string,GDynamicMenu*>(dmenu->MenuId, dmenu));
    }
    menu = menu->NextSiblingElement();
  }
  if(_menus.find(_startId)==_menus.end())
    throw Exception("start menu doesn't exist : "+_startId);
}

GMenuManager& GMenuManager::Instance(TiXmlElement* node)
{
  static GMenuManager manager;
  if(node != NULL)
    manager.Initialyze(node);

  return manager;
}

void GMenuManager::InitializeComponents()
{
	for(map<string,GDynamicMenu*>::iterator ite = _menus.begin(); ite != _menus.end(); ite++)
	{
    ite->second->SetSize(552,135);
		ite->second->SetPosition(44,142);
		ite->second->BackgroundColor(Colors::Transparent());
	}
}

void GMenuManager::Menu_NavigateRequested(Libwiisys::Object* sender, NavigateEventArgs* args)
{
	if(args->NavigateTo == "loader")
		Visible(false);
	else if(args->NavigateTo == "execution")
	{
	}
	else if(args->NavigateTo == "menu")
	{
		if(args->MenuId == "..")
		{
			if(_menuPath.size() == 1)
				throw Exception("There isn't previous menu...");
			_menuPath.pop_back();
		}
		else
		{
			if(_menus.find(_currentMenu) == _menus.end())
				throw Exception("The menu " + args->MenuId + " doesn't exists.");
			_menuPath.push_back(args->MenuId);
		}
		Invalidate();
	}
}

void GMenuManager::EnsureItems()
{
	if(_currentMenu != "")
	{
		RemoveChildren(_menus[_currentMenu]);
		_menus[_currentMenu]->NavigateRequested -= MakeDelegate(this, &GMenuManager::Menu_NavigateRequested);
		_currentMenu = _menuPath.back();
	}
	
	AddChildren(_menus[_currentMenu]);
	_menus[_currentMenu]->NavigateRequested += MakeDelegate(this, &GMenuManager::Menu_NavigateRequested);
}