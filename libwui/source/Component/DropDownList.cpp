#include <Libwui/Component/DropDownList.hpp>
#include <Libwui/Resources/ImageResourceManager.hpp>
#include <Libwui/Resources/ImageResource.hpp>

using namespace Libwiisys;
using namespace Libwui::Component;
using namespace Libwui::Resources;
using namespace std;
using namespace Libwui::Events;
using namespace fastdelegate;

DropDownList::DropDownList()
{
  _bSelected.Click += MakeDelegate(this, &DropDownList::ToggleList);
	_list.RenderAsDropDown = true;
  _list.Visible(false);
	_list.SelectedItemChanged += MakeDelegate(this, &DropDownList::List_SelectedItemChanged);
}

void DropDownList::AddItem(Libwiisys::Object* item, const std::string& text)
{
  _list.AddItem(item, text);
  if(_list.Items().size() == 1)
    _list.SelectedItem(_list.Items()[0]);
}

void DropDownList::AddItem(ListItemData d)
{
  _list.AddItem(d);
  if(_list.Items().size() == 1)
    _list.SelectedItem(_list.Items()[0]);
}

void DropDownList::List_SelectedItemChanged(Object *o, CursorEventArgs* args)
{
  _bSelected.Text(_list.SelectedItem()->Text());
	if(_list.Visible())
		ToggleList(NULL, NULL);
	
	if(_list.Items().size() != 1)
	  OnSelectedItemChanged(args->Controller());
}

void DropDownList::OnSelectedItemChanged(Device::PadController &c)
{
	SelectedItemChanged(this, new CursorEventArgs(c));
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
  if(_list.SelectedItem() != NULL)
    _bSelected.Text(_list.SelectedItem()->Text());
  Control::InitializeComponents();
  Invalidate();
}

void DropDownList::SetButtonText(string s)
{
  _bSelected.Text(s);
}

void DropDownList::ToggleList(Object *o, CursorEventArgs* args)
{
	_list.Visible(!_list.Visible());
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

void DropDownList::UpOverImage(string image)
{
  _list.UpOverImage(image);

}

void DropDownList::DownOverImage(string image)
{
  _list.DownOverImage(image);
}

ListItem* DropDownList::SelectedItem()
{
	return _list.SelectedItem();
}

void DropDownList::SelectedItem(ListItem* item)
{
	_list.SelectedItem(item);
}

const std::vector<ListItem*>& DropDownList::Items()
{
	return _list.Items();
}

void DropDownList::SetButtonFont(const std::string& font)
{
	_bSelected.SetFont(font);
}

void DropDownList::SetButtonForeColor(GXColor c)
{
	_bSelected.ForeColor(c);
}

void DropDownList::SetButtonTextSize(int pt)
{
	_bSelected.TextSize(pt);
}