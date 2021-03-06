#include <sstream>
#include <Libwui/Component/Button.hpp>
#include <Libwui/UIManager.hpp>
#include <Libwui/video.h>
#include <Libwui/Resources/ImageResource.hpp>
#include <Libwui/Resources/ImageResourceManager.hpp>

using namespace Libwui;
using namespace Libwui::Component;
using namespace Libwui::Resources;
using namespace Libwui::Device;
using namespace std;

Button::Button()
    : _lblText("", 12, (GXColor)
           {
             0,0,0,255
           }
           , 10),
_triggerState(false)
{}

Button::~Button()
{
  UIManager::SetTrigger(*this, 0);
}

void Button::InitializeComponents()
{
  _currentImage = _defaultImage;
  AddChildren(&_lblText);
  Control::InitializeComponents();
}

string Button::CurrentImage()
{
  return _currentImage;
}

void Button::ProcessMessage(Message& message)
{
  if (message.GetComponentId() != _fullId)
  {
    Control::ProcessMessage(message);
    return;
  }

  string tag = message.GetTag();
  stringstream params(message.GetSerializedParameters());

  if (tag == "DefaultImage")
    DefaultImage(params.str());
  else if (tag == "OverImage")
    OverImage(params.str());
  else if (tag == "ClickedImage")
    ClickedImage(params.str());
  else
    Control::ProcessMessage(message);
}

void Button::DefaultImage(const string& imagePath)
{
  if (InvokeRequired())
  {
    Message* m = new Message(_fullId, "DefaultImage", imagePath);
    UIManager::AddMessage(m);
  }
  else
  {
    if (_currentImage == _defaultImage)
      _currentImage = imagePath;

    _defaultImage = imagePath;
  }
}

string Button::DefaultImage() const
{
  return _defaultImage;
}

void Button::OverImage(const string& imagePath)
{
  if (InvokeRequired())
  {
    Message* m = new Message(_fullId, "DefaultImage", imagePath);
    UIManager::AddMessage(m);
  }
  else
  {
    if (_currentImage == _overImage)
      _currentImage = imagePath;

    _overImage = imagePath;
  }
}

string Button::OverImage() const
{
  return _overImage;
}

void Button::ClickedImage(const string& imagePath)
{
  if (InvokeRequired())
  {
    Message* m = new Message(_fullId, "DefaultImage", imagePath);
    UIManager::AddMessage(m);
  }
  else
  {
    if (_currentImage == _clickedImage)
      _currentImage = imagePath;

    _clickedImage = imagePath;
  }
}

string Button::ClickedImage() const
{
  return _clickedImage;
}

void Button::ProcessTrigger(PadController& c, string rootElementId)
{
  if(_fullId.find(rootElementId) != 0)
    return;

  _triggerState = true;
  OnClick(c);
  _triggerState = false;
}

void Button::OnClick(PadController &c)
{
  bool validForNonTrigger = !_triggerState && ((c.btns_c & ((u16)WPAD_BUTTON_A)) != 0);

  if (Enabled() && (_triggerState || validForNonTrigger))
    Control::OnClick(c);
}

void Button::DefineTrigger(u32 flag)
{
  UIManager::SetTrigger(*this, flag);
}

void Button::OnCursorEnter()
{
  if (_overImage != "")
    _currentImage = _overImage;

  Control::OnCursorEnter();
}

void Button::OnCursorLeave()
{
  _currentImage = _defaultImage;
  Control::OnCursorLeave();
}

void Button::OnCursorButtonDown(Device::PadController &c)
{
  if (_clickedImage != "")
    _currentImage = _clickedImage;
  Control::OnCursorButtonDown(c);
}

void Button::OnCursorButtonUp(Device::PadController &c)
{
  if (_overImage != "")
    _currentImage = _overImage;
  else
    _currentImage = _defaultImage;

  Control::OnCursorButtonUp(c);
}

void Button::Draw()
{
  ImageResource* image = Enabled() ? ImageResourceManager::Get(_currentImage)
                         : ImageResourceManager::Get(_defaultImage);
  u8 alpha = Enabled() ? 255 : 50;
  Menu_DrawImg(GetLeft(), GetTop(), image->Width(), image->Height(),
               image->Image(), 0, 1, 1, alpha);
  Control::Draw();
}

void Button::SetTextAlignement(HAlign halign, VAlign valign)
{
  _lblText.SetTextAlignment(halign,valign);
}

HAlign Button::TextHorizontalAlignement() const
{
  return _lblText.HorizontalAlignement();
}

VAlign Button::TextVerticalAlignement() const
{
  return _lblText.VerticalAlignement();
}

void Button::Text(const std::string& text)
{
  _lblText.Text(text.c_str());
}

void Button::ForeColor(GXColor c)
{
  _lblText.ForeColor(c);
}

void Button::TextSize(int pt)
{
  _lblText.FontSize(pt);
}

void Button::SetFont(const string& font)
{
  _lblText.SetFont(font);
}
