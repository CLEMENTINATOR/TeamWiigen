#include <sciifii/ui/graphic/GDynamicMenu.h>
#include <Libwiisys/String/UtilString.h>
#include <sciifii/ui/graphic/MenuItems/GMenuItemFactory.h>
#include <sciifii/Config.h>
#include <FastDelegate.h>

using namespace std;
using namespace fastdelegate;
using namespace Libwiisys::String;
using namespace Libwiisys::Exceptions;

GDynamicMenu::GDynamicMenu(TiXmlElement* node)
  : _nbSkip(0)
{
	string nodeValue = UtilString::ToStr(node->Value());
	if (nodeValue != "menu")
		throw Exception("Can't create DynamicMenu from an other tag than menu");
	MenuId = UtilString::ToStr(node->Attribute("id"), "");
	if (MenuId == "")
		throw Exception("Can't create DynamicMenu with no MenuId");

	TiXmlElement* item = node->FirstChildElement();
	while (item != NULL)
	{
		if (item->Type() != TiXmlElement::COMMENT)
		{
			GMenuItem *mitem = GMenuItemFactory::CreateItem(item);
			mitem->NavigateRequested += MakeDelegate(this,	&GDynamicMenu::Item_NavigateRequested);
			mitem->SwitchSelectionChanged += MakeDelegate(this,	&GDynamicMenu::Item_SwitchSelectionChanged);
			items.push_back(mitem);
		}
		item = item->NextSiblingElement();
	}

	_btnDown.Click += MakeDelegate(this, &GDynamicMenu::btnDown_Clicked);
	_btnUp.Click += MakeDelegate(this, &GDynamicMenu::btnUp_Clicked);
}

GDynamicMenu::~GDynamicMenu()
{
	for (vector<GMenuItem*>::iterator ite = items.begin(); ite != items.end(); ite++)
	{
		(*ite)->NavigateRequested -= MakeDelegate(this,	&GDynamicMenu::Item_NavigateRequested);
		(*ite)->SwitchSelectionChanged -= MakeDelegate(this, &GDynamicMenu::Item_SwitchSelectionChanged);
		delete *ite;
	}
}

void GDynamicMenu::InitializeComponents()
{
	//Mettre en place les deux boutons
	for (vector<GMenuItem*>::iterator ite = items.begin(); ite != items.end(); ite++)
		AddChildren(*ite);

	Control::InitializeComponents();
}

void GDynamicMenu::Item_SwitchSelectionChanged(Object* sender, SwitchEventArgs* args)
{
	if(!args->Incremental)
		Config::ClearSwitches();
	for(vector<Switch>::iterator ite = args->Switches.begin(); ite != args->Switches.end(); ite++)
		Config::SetSwitch(*ite);
}

void GDynamicMenu::Item_NavigateRequested(Object* sender, NavigateEventArgs* args)
{
	if(args->ValidateCurrentMenu)
	{
		for (vector<GMenuItem*>::iterator ite = items.begin(); ite != items.end(); ite++)
			(*ite)->Validate();
	}
	else
	{
		for (vector<GMenuItem*>::iterator ite = items.begin(); ite != items.end(); ite++)
			(*ite)->Cancel();
	}

	NavigateRequested(this, args);
}

void GDynamicMenu::EnsureItems()
{
	u32 offsetY = 12;
	for(u32 index = 0; index < items.size(); index++)
	{
		GMenuItem* item = (GMenuItem*)items[index];
		if(index < _nbSkip)
			item->Visible(false);
		else if(((s32)offsetY + item->GetHeight()) > GetHeight())
		{
			_btnDown.Enabled(true);
			item->Visible(false);
		}
		else
		{
			item->Visible(true);
			item->SetPosition(12, 12);
			offsetY += item->GetHeight() + 12;
		}
	}
}

void GDynamicMenu::btnUp_Clicked(Object* sender, Libwui::Events::CursorEventArgs* args)
{
	_nbSkip--;
	_btnUp.Enabled(_nbSkip != 0);
	_btnDown.Enabled(false);
	Invalidate();
}

void GDynamicMenu::btnDown_Clicked(Object* sender, Libwui::Events::CursorEventArgs* args)
{
	_nbSkip++;
	_btnUp.Enabled(true);
	_btnDown.Enabled(false);
	Invalidate();
}
