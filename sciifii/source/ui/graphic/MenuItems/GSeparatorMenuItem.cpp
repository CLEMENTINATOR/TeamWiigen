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
	BackgroundImage("sd:/sciifii/default/separator.png");
	Control::InitializeComponents();
}