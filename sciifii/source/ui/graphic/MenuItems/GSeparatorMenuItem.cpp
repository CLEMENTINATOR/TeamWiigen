#include <sciifii/ui/graphic/MenuItems/GSeparatorMenuItem.h>

GSeparatorMenuItem::GSeparatorMenuItem(TiXmlElement* node)
    : GMenuItem(node)
{
	BreakBefore = true;
	BreakAfter = true;
}

void GSeparatorMenuItem::InitializeComponents()
{
	SetSize(552,20);
	BackgroundImage("separator.png");
	Control::InitializeComponents();
}