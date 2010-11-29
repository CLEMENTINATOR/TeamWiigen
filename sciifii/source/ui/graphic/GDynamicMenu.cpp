#include <sciifii/ui/graphic/GDynamicMenu.h>
#include <Libwiisys/String/UtilString.h>
#include <Libwiisys/Exceptions/Exception.h>
#include <sciifii/ui/graphic/MenuItems/GMenuItemFactory.h>
#include <sciifii/Config.h>
#include <FastDelegate.h>

using namespace std;
using namespace fastdelegate;
using namespace Libwui;
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
	_btnDown.SetSize(36,36);
	_btnDown.Enabled(false);
	_btnDown.SetPosition(0, -3);
	_btnDown.VerticalAlignement(VAlign_Bottom);
	_btnDown.HorizontalAlignement(HAlign_Center);
	_btnDown.DefaultImage("Down_Default.png");
  _btnDown.OverImage("Down_Over.png");
  _btnDown.ClickedImage("Down_Clicked.png");
	_btnDown.DefineTrigger(WPAD_BUTTON_DOWN);
	AddChildren(&_btnDown);
	
	_btnUp.SetSize(36,36);
	_btnUp.Enabled(false);
	_btnUp.SetPosition(0, 9);
	_btnUp.HorizontalAlignement(HAlign_Center);
	_btnUp.DefaultImage("Up_Default.png");
  _btnUp.OverImage("Up_Over.png");
  _btnUp.ClickedImage("Up_Clicked.png");
	_btnUp.DefineTrigger(WPAD_BUTTON_UP);
	AddChildren(&_btnUp);
	
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
	u32 offsetY = 48;
	u32 offsetX = 12;
	u32 currentLine = 0;
	s32 maxHeight = 0;

	for(u32 index = 0; index < items.size(); index++)
	{
		GMenuItem* item = (GMenuItem*)items[index];

		//detect when we need to put new lines
		if((item->BreakBefore && offsetX != 12) || ((s32)offsetX + item->GetWidth()) > GetWidth() - 12)
		{
			offsetX = 12;
			if(currentLine >= _nbSkip)
				offsetY += 3 + maxHeight;
			currentLine++;
			maxHeight = 0;
		}

		//getting the max height item of the line
		if(maxHeight < item->GetHeight())
			maxHeight = item->GetHeight();

		//setting the items position and visibility
		if(currentLine < _nbSkip)
			item->Visible(false);
		else if(((s32)offsetY + item->GetHeight() + 48) > GetHeight())
		{
			_btnDown.Enabled(true);
			item->Visible(false);
		}
		else
		{
			item->Visible(true);
			item->SetPosition(offsetX, offsetY);
		}
		
		//setting the Position for the next item
		if(item->BreakAfter)
		{
			offsetX = 12;
			offsetY += maxHeight + 3;
			maxHeight = 0;
			currentLine++;
		}
		else
			offsetX += item->GetWidth() + 12;
	}
	
	Control::EnsureItems();
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

void GDynamicMenu::Reset()
{
	for (vector<GMenuItem*>::iterator ite = items.begin(); ite != items.end(); ite++)
		(*ite)->Reset();
}
