#include <iostream>
#include <Libwiisys/Object.h>
#include <sciifii/ui/graphic/MenuItems/GMenuItem.h>
#include <Libwiisys/String/UtilString.h>

using namespace std;
using namespace Libwiisys;
using namespace Libwiisys::String;

GMenuItem::GMenuItem(TiXmlElement* node)
    : _text(),
    BreakBefore(false),
    BreakAfter(false)
{
  _text = UtilString::ToStr(node->Attribute("text"),"");
}

void GMenuItem::Validate()
{}

void GMenuItem::Cancel()
{}

void GMenuItem::Reset()
{}

void GMenuItem::OnNavigate(NavigateEventArgs& args)
{
  NavigateRequested(this, &args);
}

void GMenuItem::OnModifySwitch(SwitchEventArgs& args)
{
  SwitchSelectionChanged(this, &args);
}
