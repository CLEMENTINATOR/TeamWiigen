#include <libwui.h>

using namespace Libwui;
using namespace Libwui::Component;
using namespace Libwui::Resources;
using namespace Libwui::Events;
using namespace std;

Checkbox::Checkbox() :
	_ckeckboxText("", 12, (GXColor)
	{	0,0,0,255}), _checked(false),_currentAlign(HAlign_Right)
{
	_ckeckboxText.SetTextAlignment(HAlign_Center, VAlign_Middle);
}

Checkbox::~Checkbox()
{
}

void Checkbox::InitializeComponents()
{
	_currentImage = _defaultImage;
	CurrentAlign(_currentAlign);
	AddChildren(&_ckeckboxText);
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
	else if (tag == "CurrentAlign")
	{
		int align;
		params >> align;
		CurrentAlign((HAlign) align);
	}

	else
		Control::ProcessMessage(message);
}
void Checkbox::Text(const string& str)
{

}

void Checkbox::CurrentAlign(const HAlign& align)
{
	if (InvokeRequired())
	{
		stringstream params;
		params << (int)align;
		Message* m = new Message(_fullId, "CurrentAlign",params.str());
		UIManager::AddMessage(m);
		return;
	}

	else
	{
		_currentAlign=align;
		ImageResource* image = Enabled() ? ImageResourceManager::Get(
				_currentImage) : ImageResourceManager::Get(_defaultImage);
		if (align == HAlign_Center || align == HAlign_Right)
		{
			_ckeckboxText.SetPosition(15 + image->Width(),0);
		}
		else if (align == HAlign_Left)
		{
			u32 s= _ckeckboxText.FontSize() * _ckeckboxText.Text().length() / 2;
			if(s<0)_ckeckboxText.SetPosition(0,0);
			else _ckeckboxText.SetPosition(s,0);
		}

	}
}

void Checkbox::DefaultImage(const string& imagePath)
{
	if (InvokeRequired()) // si on apelle la fct depuis un autre thread que l'ui thread
	{
		Message* m = new Message(_fullId, "DefaultImage", imagePath);
		UIManager::AddMessage(m); // On enfile le msg
		return;
	}

	else
	{
		if (_currentImage == _defaultImage)
		{
			_currentImage = imagePath;
		}
		_defaultImage = imagePath;
	}
}

void Checkbox::CheckedImage(const string& imagePath)
{
	if (InvokeRequired())
	{
		Message* m = new Message(_fullId, "CheckedImage", imagePath);
		UIManager::AddMessage(m);
		return;
	}

	else
	{
		if (_currentImage == _checkedImage)
		{
			_currentImage = imagePath;
		}
		_checkedImage = imagePath;
	}
}

string Checkbox::DefaultImage() const
{
	return _defaultImage;
}

string Checkbox::CheckedImage() const
{
	return _checkedImage;
}

void Checkbox::SetTextAlignement(HAlign halign, VAlign valign)
{
	_ckeckboxText.HorizontalAlignement(halign);
	_ckeckboxText.VerticalAlignement(valign);
}

HAlign Checkbox::TextHorizontalAlignement() const
{
	return _ckeckboxText.HorizontalAlignement();
}

VAlign Checkbox::TextVerticalAlignement() const
{
	return _ckeckboxText.VerticalAlignement();
}

void Checkbox::Text(const std::string& text)
{
	_ckeckboxText.Text(text.c_str());
}

void Checkbox::ForeColor(GXColor c)
{
	_ckeckboxText.ForeColor(c);
}

void Checkbox::TextSize(int pt)
{
	_ckeckboxText.FontSize(pt);
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
	CurrentAlign(_currentAlign);

	if (Enabled())
	{

		Control::OnClick(c);
	}
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

void Checkbox::Draw()
{
	ImageResource* image = Enabled() ? ImageResourceManager::Get(_currentImage)
			: ImageResourceManager::Get(_defaultImage);
	u8 alpha = Enabled() ? 255 : 50;
	Menu_DrawImg(GetLeft(), GetTop(), image->Width(), image->Height(),
			image->Image(), 0, 1, 1, alpha);
	Control::Draw();
}
