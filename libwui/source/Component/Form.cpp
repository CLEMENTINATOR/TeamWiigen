#include <iostream>
#include <Libwui/Component/Form.hpp>

using namespace Libwui;
using namespace Libwui::Component;
using namespace Libwui::Device;
using namespace std;

Form::Form()
    : _root(NULL),
			isRoot(false)
{}

void Form::SetRoot(bool root, const string& id)
{
  isRoot = root;
  if(root)
    SetId(id);
}

bool Form::IsInUITree()
{
  if(isRoot)
    return true;
  else
    return Control::IsInUITree();
}

void Form::MakeModal(Form* rootForm)
{
	_root = rootForm;
}

Control* Form::Parent()
{
	if(_root)
		return _root;
	else
		return Control::Parent();
}