#include <iostream>
#include <FastDelegate.h>
#include <Libwiisys/Exceptions/Exception.h>
#include <Libwiisys/String/UtilString.h>
#include <sciifii/Config.h>
#include <sciifii/ui/text/VirtualPad.h>
#include <sciifii/ui/text/Disclaimer.h>
#include <sciifii/ui/text/MenuItems/MenuItemFactory.h>
#include <sciifii/ui/text/DynamicMenu.h>

using namespace std;
using namespace fastdelegate;
using namespace Libwiisys;
using namespace Libwiisys::String;
using namespace Libwiisys::Exceptions;

DynamicMenu::DynamicMenu(TiXmlElement* node) :
    MenuBase(), selectIndex(0)
{
  string nodeValue = UtilString::ToStr(node->Value());
  if (nodeValue != "menu")
    throw Exception("Can't create DynamicMenu from an other tag than menu");
  MenuId = UtilString::ToStr(node->Attribute("id"),"");
  if (MenuId == "")
    throw Exception("Can't create DynamicMenu with no MenuId");


  _title = UtilString::ToStr(node->Attribute("title"),"");
  _message = UtilString::ToStr(node->Attribute("message"),"");

  TiXmlElement* item = node->FirstChildElement();
  while (item != NULL)
  {
    if (item->Type() != TiXmlNode::TINYXML_COMMENT)
    {
      MenuItem *mitem = MenuItemFactory::CreateItem(item);
      mitem->NavigateRequested += MakeDelegate(this,
                                  &DynamicMenu::NavigateRequested);
      mitem->SwitchSelectionChanged += MakeDelegate(this,
                                       &DynamicMenu::SwitchSelectionChanged);
      items.push_back(mitem);
    }
    item = item->NextSiblingElement();
  }

  if(items.begin() != items.end())
    items.front()->Selected = true;
}

DynamicMenu::~DynamicMenu()
{
  for (vector<MenuItem*>::iterator ite = items.begin(); ite != items.end(); ite++)
  {
    (*ite)->NavigateRequested -= MakeDelegate(this, &DynamicMenu::NavigateRequested);
    (*ite)->SwitchSelectionChanged -= MakeDelegate(this, &DynamicMenu::SwitchSelectionChanged);
    delete *ite;
  }
}

void DynamicMenu::Display()
{
  Disclaimer::Show();

  if(!_title.empty())
	cout<< _title << endl << endl;

  if(!_message.empty())
	cout<<_message << endl << endl;

  cout << endl;

  for (vector<MenuItem*>::iterator ite = items.begin(); ite != items.end(); ite++)
  {
    (*ite)->Render();
    cout << endl;
  }

  // Wait for the next frame
  VIDEO_WaitVSync();
}

NavigateEventArgs DynamicMenu::Show()
{
  nav.NavigateTo = "menu";
  nav.MenuId = MenuId;

  while (nav.NavigateTo == "menu" && nav.MenuId == MenuId)
  {
    Display();
    u32 command = GetCommand();
    s32 nextItem = selectIndex;
    if (command & vpb_Down)
    {
      do
      {
        nextItem++;
      }
      while (nextItem < (s32)items.size() && !items.at(nextItem)->Selectable);

      if (nextItem < (s32)items.size())
      {
        items.at(selectIndex)->Selected = false;
        selectIndex = nextItem;
        items.at(selectIndex)->Selected = true;
      }
    }
    else if (command & vpb_Up)
    {
      do
      {
        nextItem--;
      }
      while (nextItem >= 0 && !items.at(nextItem)->Selectable);

      if (nextItem >= 0)
      {
        items.at(selectIndex)->Selected = false;
        selectIndex = nextItem;
        items.at(selectIndex)->Selected = true;
      }
    }
    else
    {
      items.at(selectIndex)->ButtonPressed(command);
    }
  }

  return nav;
}

void DynamicMenu::SwitchSelectionChanged(Object* sender, SwitchEventArgs* args)
{
  if(!args->Incremental)
    Config::ClearSwitches();
  for(vector<Switch>::iterator ite = args->
                                     Switches.begin();
      ite != args->Switches.end();
      ite++)
    Config::SetSwitch(*ite);
}

void DynamicMenu::NavigateRequested(Object* sender, NavigateEventArgs* args)
{
  nav = *args;
  if(nav.ValidateCurrentMenu)
  {
    for (vector<MenuItem*>::iterator ite = items.begin(); ite != items.end(); ite++)
    {
      (*ite)->Validate();
    }
  }
  else
  {
    for (vector<MenuItem*>::iterator ite = items.begin(); ite != items.end(); ite++)
    {
      (*ite)->Cancel();
    }
  }
}

void DynamicMenu::Reset()
{
	for (vector<MenuItem*>::iterator ite = items.begin(); ite != items.end(); ite++)
		(*ite)->Reset();
}
