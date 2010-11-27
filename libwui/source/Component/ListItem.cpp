#include <Libwui/Component/ListItem.h>
#include <Libwui/Resources/Colors.h>
#include <Libwui/UIManager.hpp>
#include <sstream>

using namespace Libwui::Component;
using namespace Libwui::Resources;
using namespace Libwui::Device;
using namespace Libwiisys;
using namespace std;

ListItem::ListItem(ListItemData data)
    : _lbl("", 12, Colors::Black()),
    _overBackgroundColor(Colors::FromRGBA(150, 150, 150, 255)),
    _defaultBackgroundColor(Colors::FromRGBA(200, 200, 200, 255))
{
  _data = data;
  _lbl.SetTextAlignment(HAlign_Center, VAlign_Middle);
  if (data.text != "")
    _lbl.Text(data.text);
  BackgroundColor(_defaultBackgroundColor);
}

void ListItem::InitializeComponents()
{
  AddChildren(&_lbl);
  Control::InitializeComponents();
}

void ListItem::OverBackgroundColor(GXColor color)
{
  if (InvokeRequired())
  {
    stringstream argStream;
    argStream << color.r << " " << color.g << " " << color.b << " " << color.a;
    Message* m = new Message(_fullId, "OverBackgroundColor", argStream.str());
    UIManager::AddMessage(m);
    return;
  }
  else
    _overBackgroundColor = color;
}

GXColor ListItem::OverBackgroundColor()
{
	return _overBackgroundColor;
}

void ListItem::DefaultBackgroundColor(GXColor color)
{
  if (InvokeRequired())
  {
    stringstream argStream;
    argStream << color.r << " " << color.g << " " << color.b << " " << color.a;
    Message* m = new Message(_fullId, "DefaultBackgroundColor", argStream.str());
    UIManager::AddMessage(m);
    return;
  }
  else
    _defaultBackgroundColor = color;
}

GXColor ListItem::DefaultBackgroundColor()
{
	return _defaultBackgroundColor;
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
  else if (tag == "DefaultBackgroundColor")
  {
    u8 r, g, b, a;
    params >> r >> g >> b >> a;
    DefaultBackgroundColor(Colors::FromRGBA(r, g, b, a));
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
  Control::BackgroundColor(_defaultBackgroundColor);
}

void ListItem::Draw()
{
  _lbl.Text(Text());
  Control::Draw();
}

string ListItem::Text()
{
  if(_data.text == "" && _data.data != NULL)
    return _data.data->ToString();
  else
    return _data.text;
}

Object* ListItem::Value()
{
  return _data.data;
}
