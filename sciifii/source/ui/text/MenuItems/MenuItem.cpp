#include <iostream>
#include <Sciifii.h>

using namespace std;
using namespace Libwiisys::String;
using namespace Libwiisys::Exceptions;

MenuItem::MenuItem(TiXmlElement* node)
  : _text(),
	  Selected(false)
{
	_text = UtilString::ToStr(node->Attribute("text"),"");
	if(_text == "")
		throw Exception("Can't find the text to display from the XML");
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