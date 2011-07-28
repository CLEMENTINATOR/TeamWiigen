#include <FastDelegate.h>
#include <sciifii/ui/graphic/GMenuManager.h>
#include <sciifii/Sciifii.h>
#include <sciifii/Config.h>
#include <Libwui/Resources/Colors.h>
#include <Libwiisys/String/UtilString.h>
#include <Libwiisys/Exceptions/Exception.h>
#include <Libwui/UIManager.hpp>
#include <sciifii/ui/graphic/GSciifiiLauncher.h>
#include <Libwui/UIManager.hpp>
#include <Libwiisys/Exceptions/AbortException.h>
#include <sciifii/business/common/ExitSciifiiException.h>

using namespace std;
using namespace fastdelegate;
using namespace Libwiisys::String;
using namespace Libwiisys::Exceptions;
using namespace Libwui::Resources;
using namespace Libwui::Events;
using namespace Libwui;

GMenuManager::GMenuManager()
{
  BackgroundImage("advanced_screen.png");
  SetSize(640, 480);
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
  _currentMenu = _startId;
  if(_startId=="")
    throw Exception("No start menu specified !");
  _menuPath.push_back(_startId);

  TiXmlElement* menu = node->FirstChildElement();
  while (menu != NULL)
  {
    if (menu->Type() != TiXmlNode::TINYXML_COMMENT)
    {
      GDynamicMenu *dmenu = new GDynamicMenu(menu);
      _menus.insert(pair<string,GDynamicMenu*>(dmenu->MenuId, dmenu));
    }
    menu = menu->NextSiblingElement();
  }
  if(_menus.find(_startId)==_menus.end())
    throw Exception("start menu doesn't exist : " + _startId);
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
    ite->second->SetSize(552,230);
    ite->second->SetPosition(44,142);
    ite->second->BackgroundColor(Colors::Transparent());
  }

  mb.SetTitlePosition(16, 2);
  mb.SetTitleSize(279, 14);
  mb.SetTextPosition(16, 64);
  mb.SetTextSize(279, 45);
  mb.SetButtonPosition(76, 137);
  mb.DefaultButtonImage("go_button.png");
  mb.OverButtonImage("go_button_over.png");
  mb.SetMessageBoxImage("error_popup_screen.png");
  mb.UpDefaultImage("arrow_up.png");
  mb.UpOverImage("arrow_up_over.png");
  mb.UpClickedImage("arrow_up.png");
  mb.DownDefaultImage("arrow_down.png");
  mb.DownOverImage("arrow_down_over.png");
  mb.DownClickedImage("arrow_down.png");
  mb.ScrollBarImage("scrollbar.png");
  mb.ScrollBallImage("scrollball.png");

  btnExit.DefaultImage("exitbutton_normal.png");
  btnExit.OverImage("exitbutton_over.png");
  btnExit.SetSize(44, 44);
  btnExit.SetPosition(580, 415);
  btnExit.Click += MakeDelegate(this, &GMenuManager::Exit);
  btnExit.DefineTrigger(WPAD_BUTTON_HOME);

  _themeDdl.SetPosition(420, 5);
  _themeDdl.SetSize(80, 80);

  AddChildren(&btnExit);
  AddChildren(&_themeDdl);
	
  Form::InitializeComponents();
}

void GMenuManager::Exit(Object* sender, CursorEventArgs* args)
{
  Visible(false);
}

void GMenuManager::Menu_NavigateRequested(Libwiisys::Object* sender, NavigateEventArgs* args)
{
  if(args->NavigateTo == "loader")
    Visible(false);
  else if(args->NavigateTo == "execution")
  {
    if(!ExecuteSciifii())
      Visible(false);
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
  }
  _currentMenu = _menuPath.back();
  if(_menus.find(_currentMenu) == _menus.end())
    throw Exception("The requested menu \"" + _currentMenu + "\" doesn't exist.");
  AddChildren(_menus[_currentMenu]);
  _menus[_currentMenu]->NavigateRequested += MakeDelegate(this, &GMenuManager::Menu_NavigateRequested);

  Form::EnsureItems();
}

bool GMenuManager::ExecuteSciifii()
{
  try
  {
    GSciifiiLauncher g;
    UIManager::ShowDialog(g);
    Config::Reset();
    for(map<string,GDynamicMenu*>::iterator ite = _menus.begin(); ite != _menus.end(); ite++)
      ite->second->Reset();
    return true;
  }
  catch(ExitSciifiiException& ex)
  {
    return false;
  }
  catch(Exception& ex)
  {
    mb.Show("Error", ex.ToString());
    return false;
  }
}
