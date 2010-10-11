#include <libwui.h>

using namespace Libwiisys;
using namespace Libwui::Component;
using namespace std;

void List::AddItem(Object* item,const std::string& text)
{
	_dataItems.push_back((ListItemData){ item, text });
	Invalidate();
}

void List::EnsureItems()
{
	for(vector<ListItem*>::iterator ite = _items.begin(); ite != _items.end(); ite++)
		delete *ite;
		
	_items.clear();
	
	u32 nbItems = 0;
	for(vector<ListItemData>::iterator ite = _dataItems.begin(); ite != _dataItems.end(); ite++)
	{
		ListItem* i = new ListItem(*ite);
		i->SetSize(GetWidth(), 20);
		i->SetPosition(0, GetHeight() + nbItems * 20);
		_items.push_back(i);
	}
}

void List::SetSize(s32 w, s32 h)
{
	Control::SetSize(w, h);
	Invalidate();
}