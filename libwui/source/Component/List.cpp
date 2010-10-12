#include <libwui.h>
#include <fastdelegate.h>

using namespace Libwui::Component;
using namespace Libwui::Device;
using namespace std;
using namespace Libwui::Resources;
using namespace Libwui::Events;
using namespace fastdelegate;

void List::AddItem(Object* item, const std::string& text)
{
	ListItem* i = new ListItem((ListItemData)
	{	item, text});
	_items.push_back(i);
	Invalidate();
}

void List::AddItem(ListItemData d)
{
	ListItem* i = new ListItem(d);
	_items.push_back(i);
	Invalidate();
}

void List::AddItem(ListItem* i)
{
	_items.push_back(i);
	Invalidate();
}

void List::InitializeComponents()
{
	_selectedIndex = 0;
	AddChildren(&_bScrollUp);
	AddChildren(&_bScrollDown);
	_maxItemsShowable = _height / 20;
	_bScrollDown.Enabled(false);
	_bScrollUp.Enabled(false);

	_bScrollUp.Click += MakeDelegate(this, &List::ScrollUp);
	_bScrollDown.Click += MakeDelegate(this, &List::ScrollDown);
	Control::InitializeComponents();
	Invalidate();
}
void List::ScrollDown(Object *o, CursorEventArgs* args)
{
	_selectedIndex++;
	if (_selectedIndex > _items.size() - _maxItemsShowable)
	{
		_selectedIndex = _items.size() - _maxItemsShowable;
	}
	Invalidate();
}
void List::ScrollUp(Object *o, CursorEventArgs* args)
{
	_selectedIndex--;
	if (_selectedIndex < 0)
	{
		_selectedIndex = 0;
	}
	Invalidate();
}
void List::UpDefaultImage(string image)
{
	ImageResource* resource = ImageResourceManager::Get(image);
	_bScrollUp.DefaultImage(image);
	_bScrollUp.SetSize(resource->Width(), resource->Height());

}
void List::UpClickedImage(string image)
{
	ImageResource* resource = ImageResourceManager::Get(image);
	_bScrollUp.DefaultImage(image);
	_bScrollUp.SetSize(resource->Width(), resource->Height());
}
void List::DownDefaultImage(string image)
{
	ImageResource* resource = ImageResourceManager::Get(image);
	_bScrollDown.DefaultImage(image);
	_bScrollDown.SetSize(resource->Width(), resource->Height());

}
void List::DownClickedImage(string image)
{
	ImageResource* resource = ImageResourceManager::Get(image);
	_bScrollDown.DefaultImage(image);
	_bScrollDown.SetSize(resource->Width(), resource->Height());
}

void List::UpOverImage(string image)
{
	ImageResource* resource = ImageResourceManager::Get(image);
	_bScrollUp.OverImage(image);
	_bScrollUp.SetSize(resource->Width(), resource->Height());
}
void List::DownOverImage(string image)
{
	ImageResource* resource = ImageResourceManager::Get(image);
	_bScrollDown.OverImage(image);
	_bScrollDown.SetSize(resource->Width(), resource->Height());

}
void List::EnsureItems()
{
	_maxItemsShowable = _height / 20;
	_bScrollUp.SetPosition(_width-_bScrollUp.GetWidth(), 0);
	_bScrollDown.SetPosition(_width-_bScrollDown.GetWidth(), _height - _bScrollDown.GetHeight());

	for (vector<ListItem*>::iterator ite = _items.begin(); ite != _items.end(); ite++)
	{
		(*ite)->Visible(false);
		(*ite)->Enabled(false);
		RemoveChildren(*ite);
	}

	u32 nbItems = 0;
	for (u32 j = _selectedIndex; j < _items.size() && nbItems
			< _maxItemsShowable; j++)
	{
		ListItem* i = _items.at(j);
		AddChildren(i);

		i->SetSize(_width-_bScrollDown.GetWidth(), 20);
		i->SetPosition(0, nbItems * 20);

		i->Visible(true);
		i->Enabled(true);
		nbItems++;

	}
}

void List::SetSize(s32 w, s32 h)
{
	Control::SetSize(w, h);
	Invalidate();
}
void List::Invalidate()
{
	Control::Invalidate();
}
void List::Draw()
{
	if (_invalidated)
	{
		EnsureItems();
		_invalidated = false;
	}
	if ((s32) (_items.size() * 20) > _height) // needs scrool
	{
		if (_selectedIndex == 0)
		{
			_bScrollUp.Visible(false);
		}
		else
		{
			_bScrollUp.Visible(true);
		}
		if (_selectedIndex == _items.size() - _maxItemsShowable)
		{
			_bScrollDown.Visible(false);

		}
		else
		{
			_bScrollDown.Visible(true);
		}
		_bScrollDown.Enabled(true);
		_bScrollUp.Enabled(true);
		Control::Draw();
	}
	else
	{
		_bScrollDown.Visible(false);
		_bScrollUp.Visible(false);
		_bScrollDown.Enabled(false);
		_bScrollUp.Enabled(false);
		Control::Draw();
	}

}

