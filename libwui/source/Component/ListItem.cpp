#include <libwui.h>

using namespace Libwui::Component;
using namespace Libwui::Resources;

using namespace std;

ListItem::ListItem(ListItemData* data) :
	_lbl("", 12, Colors::Black())
{
	_data = data;
	if (data != NULL)
	{
		if (data->text != "")
		{
			_lbl.Text(data->text);
		}
		else
		{
			_lbl.Text(data->data->ToString());
		}
	}
	BackgroundColor(Colors::White());
}
ListItem::~ListItem()
{

}
void ListItem::InitializeComponents()
{
	Control::BackgroundColor(_normalBackgroundColor);
	AddChildren(&_lbl);
	Control::InitializeComponents();
}
void ListItem::Text(string str)
{
	_lbl.Text(str);
}
void ListItem::OverBackgroundColor(GXColor color)
{
	if (InvokeRequired())
	{
		stringstream argStream;
		argStream << color.r << " " << color.g << " " << color.b << " "
				<< color.a;
		Message* m = new Message(_fullId, "OverBackgroundColor",
				argStream.str());
		UIManager::AddMessage(m);
		return;
	}
	else
		_overBackgroundColor = color;

}

void ListItem::BackgroundColor(GXColor color)
{
	if (InvokeRequired())
	{
		stringstream argStream;
		argStream << color.r << " " << color.g << " " << color.b << " "
				<< color.a;
		Message* m = new Message(_fullId, "OverBackgroundColor",
				argStream.str());
		UIManager::AddMessage(m);
		return;
	}
	else
		_normalBackgroundColor = color;

}
void ListItem::ProcessMessage(Message& message)
{
	if (message.GetComponentId() != _fullId)
	{
		Control::ProcessMessage(message);
		return;
	}

	string tag = message.GetTag();
	stringstream params(message.GetSerializedParameters());

	if (tag == "OverBackgroundColor")
	{
		u8 r, g, b, a;
		params >> r >> g >> b >> a;
		OverBackgroundColor(Colors::FromRGBA(r, g, b, a));
	}
	else if (tag == "BackgroundColor")
	{
		u8 r, g, b, a;
		params >> r >> g >> b >> a;
		BackgroundColor(Colors::FromRGBA(r, g, b, a));
	}
	else
		Control::ProcessMessage(message);
}

void ListItem::OnCursorEnter()
{
	Control::BackgroundColor(_overBackgroundColor);
}
void ListItem::OnCursorLeave()
{
	Control::BackgroundColor(_normalBackgroundColor);
}

void ListItem::Draw()
{
	Control::Draw();
}

void ListItem::EnsureItems()
{

}
