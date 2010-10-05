#include <iostream>
#include <Sciifii.h>

using namespace std;

MenuItem::MenuItem()
  : _text(),
	  _selected(false)
{}

void MenuItem::Render()
{
	cout << (_selected ? ">>>\t" : "   \t") << _text;
}

void MenuItem::ButtonPressed(u32 button)
{}

void MenuItem::Selected(const& bool s)
{
	_selected = s;
}

bool MenuItem::Selected()
{
	return _selected;
}

void MenuItem::Validate()
{}
	
void MenuItem::Cancel()
{}

void MenuItem::OnNavigate(NavigateEventArgs& args)
{
	NavigateRequested(this, args);
}

void MenuItem::OnModifyOption(OptionEventArgs& args)
{
	OptionSelectionChanged(this, args);
}