#include <libwui.h>

using namespace Libwui;
using namespace Libwui::Component;
using namespace Libwui::Resources;
using namespace Libwui::Events;
using namespace std;

Checkbox::Checkbox() 
  :	_checkBoxText("", 12, (GXColor){0,0,0,255}), 
	  _checked(false), 
		_textPosition(HAlign_Right)
{
	_checkBoxText.SetTextAlignment(_textPosition, VAlign_Middle);
}

void Checkbox::InitializeComponents()
{
	_currentImage = _defaultImage;
	AddChildren(&_checkBoxText);
	AddChildren(&_checkBoxImg);
	Control::InitializeComponents();
}

void Checkbox::ProcessMessage(Message& message)
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
	else if (tag == "CheckedImage")
		CheckedImage(params.str());
	else if (tag == "TextPosition")
	{
		int align;
		params >> align;
		TextPosition((HAlign) align);
	}
	else
		Control::ProcessMessage(message);
}

void Checkbox::TextPosition(const HAlign& align)
{
	if (InvokeRequired())
	{
		stringstream params;
		params << (int) align;
		Message* m = new Message(_fullId, "TextPosition", params.str());
		UIManager::AddMessage(m);
		return;
	}

	_textPosition = align;
	Invalidate();
}

void Checkbox::DefaultImage(const string& imagePath)
{
	if (InvokeRequired()) // si on apelle la fct depuis un autre thread que l'ui thread
	{
		Message* m = new Message(_fullId, "DefaultImage", imagePath);
		UIManager::AddMessage(m); // On enfile le msg
		return;
	}

	if (_currentImage == _defaultImage)
	{
		_currentImage = imagePath;
		Invalidate();
	}
	_defaultImage = imagePath;
}

void Checkbox::CheckedImage(const string& imagePath)
{
	if (InvokeRequired())
	{
		Message* m = new Message(_fullId, "CheckedImage", imagePath);
		UIManager::AddMessage(m);
		return;
	}

	if (_currentImage == _checkedImage)
	{
		_currentImage = imagePath;
		Invalidate();
	}
	_checkedImage = imagePath;
}

string Checkbox::DefaultImage() const
{
	return _defaultImage;
}

string Checkbox::CheckedImage() const
{
	return _checkedImage;
}

void Checkbox::Text(const std::string& text)
{
	_checkBoxText.Text(text.c_str());
	Invalidate();
}

void Checkbox::ForeColor(GXColor c)
{
	_checkBoxText.ForeColor(c);
}

void Checkbox::FontSize(int pt)
{
	_checkBoxText.FontSize(pt);
	Invalidate();
}

void Checkbox::OnClick(Libwui::Device::PadController &c)
{
	_checked = !_checked;

	if (_checked)
	{
		if (_checkedImage != "")
			_currentImage = _checkedImage;
	}
	else
	{
		_currentImage = _defaultImage;
	}
		
	Invalidate();
	Control::OnClick(c);
}

void Checkbox::OnCheckChanged(Libwui::Device::PadController &c)
{
	CursorEventArgs e(c);
	CheckChanged(this, &e);
}

bool Checkbox::Checked() const
{
	return _checked;
}

void Checkbox::EnsureItems()
{
	ImageResource* resource = ImageResourceManager::Get(_currentImage);
	_checkBoxImg.ImageLocation(_currentImage);
	_checkBoxImg.SetSize(resource->Width(), resource->Height());
	
	if (_textPosition == HAlign_Center || _textPosition == HAlign_Right)
	{
		_checkBoxImg.SetPosition(0, 0);
		_checkBoxText.SetPosition(5 + _checkBoxImg.GetWidth(), 0);
	}
	else if (_textPosition == HAlign_Left)
	{
		u32 size = (_checkBoxText.Text().length() * _checkBoxText.FontSize()) / 2;

		_checkBoxText.SetPosition(0, 0);
		_checkBoxImg.SetPosition(size + 15, 0);
		_checkBoxText.SetTextAlignment(HAlign_Left, VAlign_Middle);
	}
}