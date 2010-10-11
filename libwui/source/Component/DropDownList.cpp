#include <libwui.h>

using namespace Libwiisys;
using namespace Libwui::Component;
using namespace Libwui::Resources;
using namespace std;
using namespace Libwui::Events;
using namespace fastdelegate;

DropDownList::DropDownList()
{
	_bSelected.Click += MakeDelegate(this, &DropDownList::ShowList);
	_list.Enabled(false);
	_list.Visible(false);
}
void DropDownList::SetPosition(int x, int y)
{
	Control::SetPosition(x, y);
	Invalidate();
}
void DropDownList::AddItem(Libwiisys::Object* item, const std::string& text)
{
	_list.AddItem(item, text);
}
void DropDownList::DefaultImage(string s)
{
	_bSelected.DefaultImage(s);
	Invalidate();
}
void DropDownList::OverImage(string s)
{
	_bSelected.OverImage(s);
	Invalidate();
}
void DropDownList::InitializeComponents()
{
	AddChildren(&_list);
	AddChildren(&_bSelected);
	Control::InitializeComponents();
	Invalidate();
}
void DropDownList::SetButtonText(string s)
{
	_bSelected.Text(s);
}
void DropDownList::ShowList(Object *o, CursorEventArgs* args)
{
	if (!_list.Enabled())
	{
		_list.Enabled(true);
		_list.Visible(true);
	}
	else
	{
		_list.Enabled(false);
		_list.Visible(false);
	}
}
void DropDownList::EnsureItems()
{
	ImageResource* resource = ImageResourceManager::Get(
			_bSelected.CurrentImage());
	_bSelected.SetPosition(0, 0);
	_bSelected.SetSize(resource->Width(), resource->Height());
	_list.SetPosition(0, resource->Height());
	_list.SetSize(resource->Width(), _height);
}
void DropDownList::Draw()
{
	if (_invalidated)
	{
		EnsureItems();
		_invalidated = false;
	}
	Control::Draw();

}

void DropDownList::UpDefaultImage(string image)
{
	_list.UpDefaultImage(image);
}
void DropDownList::UpClickedImage(string image)
{
	_list.UpClickedImage(image);
}
void DropDownList::DownDefaultImage(string image)
{
	_list.DownDefaultImage(image);

}
void DropDownList::DownClickedImage(string image)
{
_list.DownClickedImage(image);
}
void  DropDownList::UpOverImage(std::string image)
{
	_list.UpOverImage(image);

}
void  DropDownList::DownOverImage(std::string image)
{
	_list.DownOverImage(image);

}
