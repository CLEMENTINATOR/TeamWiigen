#include <Libwui/Component/List.hpp>
#include <FastDelegate.h>
#include <Libwui/Resources/ImageResource.hpp>
#include <Libwui/Resources/ImageResourceManager.hpp>
#include <Libwui/Resources/Colors.h>

using namespace Libwui::Component;
using namespace Libwui::Device;
using namespace std;
using namespace Libwui::Resources;
using namespace Libwui::Events;
using namespace fastdelegate;

List::List()
  : Control(),
		RenderAsDropDown(false),
	  _startShowIndex(0),
		_selectedItem(NULL)
{}

List::~List()
{
  for(vector<ListItem*>::iterator ite = _items.begin(); ite != _items.end(); ite++)
  {
	  (*ite)->Click -= MakeDelegate(this, &List::ItemClicked);
	  delete (*ite);
  }
}

void List::AddItem(Object* item, const std::string& text)
{
	ListItem* i = new ListItem((ListItemData){item, text});
	if(!RenderAsDropDown)
		i->OverBackgroundColor(i->DefaultBackgroundColor());
	i->Click += MakeDelegate(this, &List::ItemClicked);
  _items.push_back(i);
  Invalidate();
}

void List::AddItem(const ListItemData& d)
{
	ListItem* i = new ListItem(d);
	if(!RenderAsDropDown)
		i->OverBackgroundColor(i->DefaultBackgroundColor());
	i->Click += MakeDelegate(this, &List::ItemClicked);
  _items.push_back(i);
  Invalidate();
}

void List::AddItem(const ListItem& li)
{
  ListItem* i = new ListItem(li);
	if(!RenderAsDropDown)
		i->OverBackgroundColor(i->DefaultBackgroundColor());
	i->Click += MakeDelegate(this, &List::ItemClicked);
  _items.push_back(i);
  Invalidate();
}

const vector<ListItem*>& List::Items()
{
	return _items;
}

void List::InitializeComponents()
{
  _maxItemsShowable = _height / 20;

  _bScrollUp.Click += MakeDelegate(this, &List::ScrollUp);
  _bScrollDown.Click += MakeDelegate(this, &List::ScrollDown);
	
	AddChildren(&_bScrollUp);
  AddChildren(&_bScrollDown);
	
  Control::InitializeComponents();
}

void List::ItemClicked(Object *sender, CursorEventArgs* args)
{
	SelectedItem((ListItem*)sender);
}

void List::OnSelectedItemChanged(Device::PadController &c)
{
	SelectedItemChanged(this, new CursorEventArgs(c));
}

void List::ScrollDown(Object *o, CursorEventArgs* args)
{
  if (_startShowIndex + _maxItemsShowable < _items.size())
	{
		_startShowIndex++;
    Invalidate();
	}
}

void List::ScrollUp(Object *o, CursorEventArgs* args)
{
  if (_startShowIndex > 0)
	{
    _startShowIndex--;
		Invalidate();
	}
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

	//set default button position
	_bScrollUp.SetPosition(_width - _bScrollUp.GetWidth(), 0);
	_bScrollDown.SetPosition(_width - _bScrollDown.GetWidth(), _height - _bScrollDown.GetHeight());
	
	//reset buttons states
	if ((s32)_items.size() > _maxItemsShowable) // needs scrool
  {
	  _bScrollUp.Visible(true);
    _bScrollDown.Visible(true);
    _bScrollDown.Enabled(_startShowIndex + _maxItemsShowable < _items.size());
    _bScrollUp.Enabled(_startShowIndex != 0);
  }
  else
  {
    _bScrollDown.Visible(false);
    _bScrollUp.Visible(false);
    _bScrollDown.Enabled(false);
    _bScrollUp.Enabled(false);
  }
	
	//define the current Aera
	for (u32 j = 0; j < _items.size(); j++)
  {
    ListItem* i = _items.at(j);
    RemoveChildren(i);
		
		if(j >= _startShowIndex && j - _startShowIndex < _maxItemsShowable)
		{
			if(_bScrollDown.Visible())
				i->SetSize(_width - _bScrollDown.GetWidth(), 20);
			else
				i->SetSize(_width, 20);
				
			i->SetPosition(0, (j - _startShowIndex) * 20);
			i->Visible(true);
			i->Enabled(true);
			AddChildren(i);
			
			if(j - _startShowIndex == (_maxItemsShowable - 1) && RenderAsDropDown)
				_bScrollDown.SetPosition(_width - _bScrollDown.GetWidth(), (j - _startShowIndex + 1) * 20 - _bScrollDown.GetHeight());
		}
		else
		{
			i->Visible(false);
			i->Enabled(false);
		}
  }
	
	
}

void List::SetSize(s32 w, s32 h)
{
  Control::SetSize(w, h);
  Invalidate();
}

ListItem* List::SelectedItem()
{
	return _selectedItem;
}

void List::SelectedItem(ListItem* i)
{
	if(i != _selectedItem)
	{
		for(vector<ListItem*>::iterator ite = _items.begin(); ite != _items.end(); ite++)
			if(*ite == i)
			{
				if(!RenderAsDropDown)
				{
					if(_selectedItem)
					{
						_selectedItem->DefaultBackgroundColor(Colors::White());
						_selectedItem->OverBackgroundColor(Colors::White());
					}
					(*ite)->DefaultBackgroundColor(Colors::Blue());
					(*ite)->OverBackgroundColor(Colors::Blue());
				}
				_selectedItem = *ite;
				OnSelectedItemChanged(PadController::Currents()[0]);
				break;
			}
	}
}
