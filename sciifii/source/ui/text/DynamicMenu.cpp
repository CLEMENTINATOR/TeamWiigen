#include <iostream>
#include <FastDelegate.h>
#include <Sciifii.h>

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


	TiXmlElement* item = node->FirstChildElement();
	while (item != NULL)
	{
		if (item->Type() != TiXmlElement::COMMENT)
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
}

DynamicMenu::~DynamicMenu()
{
	for (vector<MenuItem*>::iterator ite = items.begin(); ite != items.end(); ite++)
	{
		(*ite)->NavigateRequested -= MakeDelegate(this,	&DynamicMenu::NavigateRequested);
		(*ite)->SwitchSelectionChanged -= MakeDelegate(this, &DynamicMenu::SwitchSelectionChanged);
		delete *ite;
	}
}

void DynamicMenu::Display()
{
	Disclaimer::Show();

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
		u32 nextItem = selectIndex;
		if (command & vpb_Down)
		{
			do
			{
				nextItem++;
			} while (nextItem < items.size() && !items.at(nextItem)->Selectable);

			if (nextItem < items.size())
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
			} while (nextItem >= 0 && !items.at(nextItem)->Selectable);

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
	for(vector<Switch>::iterator ite = args->Switches.begin(); ite != args->Switches.end(); ite++)
		Config::SetSwitch(*ite);
}

void DynamicMenu::NavigateRequested(Object* sender, NavigateEventArgs* args)
{
	nav = *args;
}
