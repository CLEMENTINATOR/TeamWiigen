#include <Libwui/Component/MessageBox.hpp>
#include <Libwui/Resources/ImageResource.hpp>
#include <Libwui/Resources/ImageResourceManager.hpp>
#include <Libwui/UIManager.hpp>
#include <Libwui/Resources/Colors.h>

using namespace Libwui;
using namespace Libwui::Component;
using namespace Libwui::Resources;
using namespace Libwui::Events;
using namespace std;
using namespace fastdelegate;

void MessageBox::Show(std::string text, std::string title)
{
  _title.Text(title);
  _text.Text(text);
  SetPosition(0, 0);
	
  UIManager::ShowDialog(*this);
}

void MessageBox::Button_Clicked(Libwiisys::Object*sender, Events::CursorEventArgs *c)
{
  Hide();
}

void MessageBox::Hide()
{
  Visible(false);
}

MessageBox::MessageBox()
    : _title("", 12, Colors::FromRGBA(0, 0, 0, 255)),
    _text("", 12, Colors::FromRGBA(0, 0, 0, 255))
{
  BackgroundColor(Colors::FromRGBA(200, 200, 200, 175));
  _boxButton.Text("OK");
  _boxButton.Click += MakeDelegate(this, &MessageBox::Button_Clicked);
}

void MessageBox::InitializeComponents()
{
	ImageResource* resource = ImageResourceManager::Get(_boxImg.ImageLocation());
	SetSize(Parent()->GetWidth(), Parent()->GetHeight());
	_boxImg.SetPosition((Parent()->GetWidth() - resource->Width()) / 2, (Parent()->GetHeight() - resource->Height()) / 2);
	 
  AddChildren(&_boxImg);
  _boxImg.AddChildren(&_title);
  _boxImg.AddChildren(&_text);
  _boxImg.AddChildren(&_boxButton);
  Control::InitializeComponents();
}

void MessageBox::SetTitlePosition(int x, int y)
{
  _title.SetPosition(x, y);
}

void MessageBox::SetTextPosition(int x, int y)
{
  _text.SetPosition(x, y);
}

void MessageBox::SetTitleSize(int x, int y)
{
  _title.SetSize(x, y);
}

void MessageBox::SetTextSize(int x, int y)
{
  _text.SetSize(x, y);
}

void MessageBox::SetMessageBoxImage(std::string s)
{
  ImageResource* resource = ImageResourceManager::Get(s);
  _boxImg.ImageLocation(s);
  _boxImg.SetSize(resource->Width(), resource->Height());
}

void MessageBox::DefaultButtonImage(std::string s)
{
  ImageResource* resource = ImageResourceManager::Get(s);
  _boxButton.DefaultImage(s);
  _boxButton.SetSize(resource->Width(), resource->Height());
  _boxButton.DefaultImage(s);
}

void MessageBox::OverButtonImage(std::string s)
{
  _boxButton.OverImage(s);
}

void MessageBox::ClickedButtonImage(std::string s)
{
  _boxButton.ClickedImage(s);
}

void MessageBox::SetButtonPosition(int x, int y)
{
  _boxButton.SetPosition(x, y);
}

void MessageBox::SetFont(const string& font)
{
	_boxButton.SetFont(font);
	_title.SetFont(font);
  _text.SetFont(font);
}

void MessageBox::UpDefaultImage(const std::string& imagePath)
{
	_text.UpDefaultImage(imagePath);
}

std::string MessageBox::UpDefaultImage() const
{
	return _text.UpDefaultImage();
}

void MessageBox::UpOverImage(const std::string& imagePath)
{
	_text.UpOverImage(imagePath);
}

std::string MessageBox::UpOverImage() const
{
	return _text.UpOverImage();
}

void MessageBox::UpClickedImage(const std::string& imagePath)
{
	_text.UpClickedImage(imagePath);
}

std::string MessageBox::UpClickedImage() const
{
	return _text.UpClickedImage();
}

void MessageBox::DownDefaultImage(const std::string& imagePath)
{
	_text.DownDefaultImage(imagePath);
}

std::string MessageBox::DownDefaultImage() const
{
	return _text.DownDefaultImage();
}

void MessageBox::DownOverImage(const std::string& imagePath)
{
	_text.DownOverImage(imagePath);
}

std::string MessageBox::DownOverImage() const
{
	return _text.DownOverImage();
}

void MessageBox::DownClickedImage(const std::string& imagePath)
{
	_text.DownClickedImage(imagePath);
}

std::string MessageBox::DownClickedImage() const
{
	return _text.DownClickedImage();
}

void MessageBox::ScrollBarImage(const std::string& imagePath)
{
	_text.ScrollBarImage(imagePath);
}

std::string MessageBox::ScrollBarImage() const
{
	return _text.ScrollBarImage();
}

void MessageBox::ScrollBallImage(const std::string& imagePath)
{
	_text.ScrollBallImage(imagePath);
}

std::string MessageBox::ScrollBallImage() const
{
	return _text.ScrollBallImage();
}
