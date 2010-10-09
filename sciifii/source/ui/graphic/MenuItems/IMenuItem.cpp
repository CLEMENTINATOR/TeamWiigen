#include <iostream>
#include <Sciifii.h>

using namespace std;
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
	NavigateRequested(this, &args);
}

void IMenuItem::OnModifySwitch(SwitchEventArgs& args)
{
	SwitchSelectionChanged(this, &args);
}
