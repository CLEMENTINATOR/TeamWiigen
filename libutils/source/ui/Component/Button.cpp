#include <ui/Component/Button.hpp>

#include <sstream>

#include <ui/video.h>
#include <ui/UIManager.hpp>
#include <ui/Message.hpp>
#include <ui/Resources/ImageResourceManager.hpp>
#include <ui/Resources/ImageResource.hpp>

using namespace UI;
using namespace UI::Component;
using namespace UI::Resources;
using namespace std;

Button::Button() : _lblText("", 12, (GXColor){0,0,0,255})
{}

void Button::InitializeComponents()
{
	_currentImage = _defaultImage;
	AddChildren(&_lblText);
	Control::InitializeComponents();
}

void Button::ProcessMessage(Message& message)
{
	if(message.GetComponentId() != _fullId)
	{
		Control::ProcessMessage(message);
		return;
	}
	
	string tag = message.GetTag();
	stringstream params(message.GetSerializedParameters());
	
	if(tag == "DefaultImage")
		DefaultImage(params.str());
	else if(tag == "OverImage")
		OverImage(params.str());
	else if(tag == "ClickedImage")
		ClickedImage(params.str());
	else
		Control::ProcessMessage(message);
}

void Button::ChangeImage(const string _image)
{
	_currentImage = _image;
	ImageResource* image = ImageResourceManager::Get(_currentImage);
	_lblText.SetSize(image->Width(), image->Height());
}

void Button::DefaultImage(const string& imagePath)
{
	if(InvokeRequired())
	{
		Message* m = new Message(_fullId, "DefaultImage", imagePath);
		UIManager::AddMessage(m);
	}
	else
	{
		if(_currentImage == _defaultImage)
			ChangeImage(imagePath);
			
		_defaultImage = imagePath;
	}
}

string Button::DefaultImage() const
{
	return _defaultImage;
}

void Button::OverImage(const string& imagePath)
{
	if(InvokeRequired())
	{
		Message* m = new Message(_fullId, "DefaultImage", imagePath);
		UIManager::AddMessage(m);
	}
	else
	{
		if(_currentImage == _overImage)
			ChangeImage(imagePath);
			
		_overImage = imagePath;
	}
}

string Button::OverImage() const
{
	return _overImage;
}

void Button::ClickedImage(const string& imagePath)
{
	if(InvokeRequired())
	{
		Message* m = new Message(_fullId, "DefaultImage", imagePath);
		UIManager::AddMessage(m);
	}
	else
	{
		if(_currentImage == _clickedImage)
			ChangeImage(imagePath);
			
		_clickedImage = imagePath;
	}
}

string Button::ClickedImage() const
{
	return _clickedImage;
}


void Button::OnClick(UI::Device::PadController &c)
{
	if(Enabled())
		Control::OnClick(c);
}

void Button::OnCursorEnter()
{
	if(_overImage.length() > 0)
		ChangeImage(_overImage);
	Control::OnCursorEnter();
}

void Button::OnCursorLeave()
{
	ChangeImage(_defaultImage);
	Control::OnCursorLeave();
}

void Button::OnCursorButtonDown(Device::PadController &c)
{
	if(_clickedImage.length() > 0)
		ChangeImage(_clickedImage);
	Control::OnCursorButtonDown(c);
}

void Button::OnCursorButtonUp(Device::PadController &c)
{
	if(_overImage.length() > 0)
		ChangeImage(_overImage);
	else
		ChangeImage(_defaultImage);
		
	Control::OnCursorButtonUp(c);
}

void Button::Draw()
{
	ImageResource* image = Enabled() ? ImageResourceManager::Get(_currentImage) : ImageResourceManager::Get(_defaultImage);
	u8 alpha = Enabled() ? 255 : 50;
	Menu_DrawImg(GetLeft(), GetTop(), image->Width(), image->Height(), image->Image(), 0, 1, 1, alpha);
	Control::Draw();
}

void Button::SetTextAlignement(HAlign halign, VAlign valign)
{
	_lblText.HorizontalAlignement(halign);
	_lblText.VerticalAlignement(valign);
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
