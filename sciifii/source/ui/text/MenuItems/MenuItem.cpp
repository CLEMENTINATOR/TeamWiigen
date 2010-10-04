#include <iostream>
#include <Sciifii.h>

using namespace std;

MenuItem::MenuItem()
  : _text(),
	  _selected(false)
{}

void MenuItem::Render()
{
}

void MenuItem::ButtonPressed(u32 button)
{
  cout << (_selected ? ">>>\t" : "   \t") << _text;
}

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