#include <iostream>
#include <Sciifii.h>

using namespace std;
using namespace Libwiisys::String;
using namespace Libwiisys::Exceptions;

SeparatorMenuItem::SeparatorMenuItem(TiXmlElement* node)
  : MenuItem(node)
{
  _separator = UtilString::ToStr(node->Attribute("char"),"");
  Selectable = false;
}

void SeparatorMenuItem::Render()
{
  for(int i = 0; i < 20; ++i)
    cout << _separator;
}
