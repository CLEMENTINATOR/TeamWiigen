#include <iostream>
#include <Sciifii.h>

using namespace std;
using namespace Libwiisys::String;
using namespace Libwiisys::Exceptions;

SeparatorMenuItem::SeparatorMenuItem(TiXmlElement* node)
  : MenuItem(node)
{
  string nodeValue = UtilString::ToStr(node->Value());
  if(nodeValue != "separatorMenuItem")
    throw Exception("Can't create SeparatorMenuItem from the tag " + nodeValue);
	  
  _pattern = UtilString::ToStr(node->Attribute("char"),"");
  Selectable = false;
}

void SeparatorhMenuItem::Render()
{
  for(int i = 0; i < 20; ++i)
    cout << _pattern;
}