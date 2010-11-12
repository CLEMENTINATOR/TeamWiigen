#include <iostream>
#include <sciifii/ui/text/MenuItems/MenuItem.h>
#include <Libwiisys/String/UtilString.h>
#include <Libwiisys/Exceptions/Exception.h>

using namespace std;
using namespace Libwiisys::String;
using namespace Libwiisys::Exceptions;

MenuItem::MenuItem(TiXmlElement* node)
    : _text(),
      Selectable(true),
    Selected(false)

{
  _text = UtilString::ToStr(node->Attribute("text"),"");
}

void MenuItem::Render()
{
  cout << (Selected ? ">>>\t" : "   \t") << _text;
}

void MenuItem::ButtonPressed(u32 button)
{}

void MenuItem::Validate()
{}

void MenuItem::Cancel()
{}

void MenuItem::OnNavigate(NavigateEventArgs& args)
{
  NavigateRequested(this, &args);
}

void MenuItem::OnModifySwitch(SwitchEventArgs& args)
{
  SwitchSelectionChanged(this, &args);
}
