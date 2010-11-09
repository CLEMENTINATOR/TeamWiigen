#include <iostream>
#include <libwui/Component/Form.hpp>

using namespace Libwui;
using namespace Libwui::Component;
using namespace Libwui::Device;
using namespace std;

Form::Form()
    : isRoot(false)
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
