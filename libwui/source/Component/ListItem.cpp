#include <libwui/Component/ListItem.h>
#include <Libwui/Resources/Colors.h>
#include <libwui/UIManager.hpp>

using namespace Libwui::Component;
using namespace Libwui::Resources;
using namespace Libwui::Device;
using namespace std;

ListItem::ListItem(ListItemData data)
    : _lbl("", 12, Colors::Black()),
    _overBackgroundColor(Colors::Blue()),
    _normalBackgroundColor(Colors::FromRGBA(255,255,255,0))
{
  _data = data;
  _lbl.SetTextAlignment(HAlign_Center, VAlign_Middle);
  if (data.text != "")
    _lbl.Text(data.text);
}

void ListItem::InitializeComponents()
{
  BackgroundColor(_normalBackgroundColor);
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

void ListItem::NormalBackgroundColor(GXColor color)
{
  if (InvokeRequired())
  {
    stringstream argStream;
    argStream << color.r << " " << color.g << " " << color.b << " " << color.a;
    Message* m = new Message(_fullId, "NormalBackgroundColor", argStream.str());
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
  else if (tag == "NormalBackgroundColor")
  {
    u8 r, g, b, a;
    params >> r >> g >> b >> a;
    NormalBackgroundColor(Colors::FromRGBA(r, g, b, a));
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

  _lbl.Text(StringValue());
  Control::Draw();
}

string ListItem::StringValue()
{
  if(_data.text == "")
    return _data.data->ToString();
  else
    return _data.text;
}
