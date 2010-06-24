#include <ui/Component/Form.hpp>

#include <iostream>

#include <ui/UIManager.hpp>
#include <ui/video.h>

using namespace UI;
using namespace UI::Component;
using namespace UI::Device;
using namespace std;

Form::Form()
: isRoot(false)
{}

void Form::SetRoot(bool root)
{
	isRoot = root;
	if(root)
		SetId("root");
}

bool Form::IsInUITree()
{
	if(isRoot)
		return true;
	else
		return Control::IsInUITree();
}
