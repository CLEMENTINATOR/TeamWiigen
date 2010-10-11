#include <libwui.h>
#include <fastdelegate.h>

using namespace Libwui::Component;
using namespace std;
using namespace Libwui::Resources;
using namespace Libwui::Events;
using namespace fastdelegate;
void List::AddItem(Object* item, const std::string& text)
{
	_dataItems.push_back((ListItemData)
	{	item, text});
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
	_bScrollUp.SetPosition(_width, 0);
	_bScrollDown.SetPosition(_width, _height - _bScrollDown.GetHeight());
}
void List::ScrollDown(Object *o, CursorEventArgs* args)
{
	_selectedIndex++;
	if (_selectedIndex > _dataItems.size() - _maxItemsShowable)
	{
		_selectedIndex = _dataItems.size() - _maxItemsShowable;
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
	for (vector<ListItem*>::iterator ite = _items.begin(); ite != _items.end(); ite++)
	{
		RemoveChildren(*ite);
		delete *ite;
	}

	_items.clear();

	u32 nbItems = 0;
	for (u32 j = _selectedIndex; j < _dataItems.size() && nbItems
			< _maxItemsShowable; j++)
	{

		ListItem* i = new ListItem(_dataItems[j]);
		AddChildren(i);
		i->SetSize(_width, 20);
		i->SetPosition(0, nbItems * 20);
		_items.push_back(i);
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
	if ((s32) (_dataItems.size() * 20) > _height) // needs scrool
	{
		if (_selectedIndex == 0)
		{
			_bScrollUp.Visible(false);
		}
		else
		{
			_bScrollUp.Visible(true);
		}
		if (_selectedIndex == _dataItems.size() - _maxItemsShowable)
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
