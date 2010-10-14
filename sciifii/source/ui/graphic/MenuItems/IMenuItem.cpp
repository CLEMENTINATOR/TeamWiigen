#include <iostream>
#include <Libwiisys/Object.h>
#include <sciifii/ui/graphic/MenuItems/IMenuItem.h>
#include <Libwiisys/String/UtilString.h>

using namespace std;
using namespace Libwiisys;
using namespace Libwiisys::String;

IMenuItem::IMenuItem(TiXmlElement* node)
    : _text(),
    Selected(false)
{
  _text = UtilString::ToStr(node->Attribute("text"),"");
}

void IMenuItem::Validate()
{}

void IMenuItem::Cancel()
{}

void IMenuItem::OnNavigate(NavigateEventArgs& args)
{
  NavigateRequested(dynamic_cast<Object*>(this), &args);
}

void IMenuItem::OnModifySwitch(SwitchEventArgs& args)
{
  SwitchSelectionChanged(dynamic_cast<Object*>(this), &args);
}
