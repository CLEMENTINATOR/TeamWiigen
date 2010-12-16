#include <Libwui/Component/TrackBar.hpp>
#include <Libwui/UIManager.hpp>
#include <FastDelegate.h>
#include <math.h>
#include <sstream>
#include <Libwui/Control.hpp>
#include <Libwui/Resources/ImageResource.hpp>
#include <Libwui/Resources/ImageResourceManager.hpp>

using namespace std;
using namespace fastdelegate;
using namespace Libwui;
using namespace Libwui::Component;
using namespace Libwui::Events;

using namespace Libwui::Resources;

TrackBar::TrackBar()
	: _minValue(0),
	  _maxValue(100),
	  _value(0),
	  _scrollBallDrag(false),
	  _scrollBallMoved(false),
	  _mode(TrackBarMode_Vertical),
	  _modeChanged(false)
{
	_btnUp.Click += MakeDelegate(this, &TrackBar::btnUp_Clicked);
	_btnDown.Click += MakeDelegate(this, &TrackBar::btnDown_Clicked);
	_scrollBall.CursorMove += MakeDelegate(this, &TrackBar::scrollBall_move);
	_scrollBall.CursorButtonDown += MakeDelegate(this, &TrackBar::scollBall_held);
	_scrollBall.CursorButtonUp += MakeDelegate(this, &TrackBar::scrollBall_release);
}

TrackBar::~TrackBar()
{}

void TrackBar::InitializeComponents()
{
	ImageResource* resourceUp = ImageResourceManager::Get(_btnUp.DefaultImage());
	ImageResource* resourceDown = ImageResourceManager::Get(_btnDown.DefaultImage());
	ImageResource* resourceBar = ImageResourceManager::Get(_scrollBar.ImageLocation());
	ImageResource* resourceBall = ImageResourceManager::Get(_scrollBall.ImageLocation());
	if(_mode == TrackBarMode_Vertical)
	{
		_btnDown.SetPosition(0, GetHeight() - resourceDown->Height());
		_scrollBar.SetPosition(0, resourceUp->Height());
		_scrollBar.SetSize(resourceBar->Width(), GetHeight() - resourceUp->Height() - resourceDown->Height());
		_scrollBall.SetPosition((resourceBar->Width() - resourceBall->Width()) / 2, 0);
	}
	else if(_mode == TrackBarMode_Horizontal)
	{
		_btnDown.SetPosition(GetWidth() - resourceDown->Width(), 0);
		_scrollBar.SetPosition(resourceUp->Width(), 0);
		_scrollBar.SetSize(GetWidth() - resourceUp->Width() - resourceDown->Width(), resourceBar->Height());
		_scrollBall.SetPosition(0, (resourceBar->Height() - resourceBall->Height()) / 2);
	}

	_btnUp.SetPosition(0, 0);
	_btnUp.SetSize(resourceUp->Width(), resourceUp->Height());
	_btnDown.SetSize(resourceDown->Width(), resourceDown->Height());
	_scrollBar.FillMode(ResizeMode_Fill);
	_scrollBall.SetSize(resourceBall->Width(), resourceBall->Height());

	AddChildren(&_btnUp);
	AddChildren(&_scrollBar);
	AddChildren(&_btnDown);
	_scrollBar.AddChildren(&_scrollBall);

	Control::InitializeComponents();
}

void TrackBar::ProcessMessage(Message& message)
{
	if(message.GetComponentId() != _fullId)
	{
		Control::ProcessMessage(message);
		return;
	}

	string tag = message.GetTag();
	stringstream params(message.GetSerializedParameters());

	if(tag == "Value")
	{
		u32 s;
		params >> s;
		SetValue(s);
	}
	else if(tag == "MinValue")
	{
		u32 s;
		params >> s;
		SetMinValue(s);
	}
	else if(tag == "MaxValue")
	{
		u32 s;
		params >> s;
		SetMaxValue(s);
	}
	else if(tag == "Mode")
	{
		int mode;
		params >> mode;
		SetMode((TrackBarMode)mode);
	}
	else
		Control::ProcessMessage(message);
}

void TrackBar::EnsureItems()
{
	if(_modeChanged)
	{
		ImageResource* resourceUp = ImageResourceManager::Get(_btnUp.DefaultImage());
		ImageResource* resourceDown = ImageResourceManager::Get(_btnDown.DefaultImage());
		ImageResource* resourceBar = ImageResourceManager::Get(_scrollBar.ImageLocation());
		ImageResource* resourceBall = ImageResourceManager::Get(_scrollBall.ImageLocation());
		if(_mode == TrackBarMode_Vertical)
		{
			_btnDown.SetPosition(0, GetHeight() - resourceDown->Height());
			_scrollBar.SetPosition(0, resourceUp->Height());
			_scrollBar.SetSize(resourceBar->Width(), GetHeight() - resourceUp->Height() - resourceDown->Height());
			_scrollBall.SetPosition((resourceBar->Width() - resourceBall->Width()) / 2, 0);
		}
		else if(_mode == TrackBarMode_Horizontal)
		{
			_btnDown.SetPosition(GetWidth() - resourceDown->Width(), 0);
			_scrollBar.SetPosition(resourceUp->Width(), 0);
			_scrollBar.SetSize(GetWidth() - resourceUp->Width() - resourceDown->Width(), resourceBar->Height());
			_scrollBall.SetPosition(0, (resourceBar->Height() - resourceBall->Height()) / 2);
		}
		_btnUp.SetSize(resourceUp->Width(), resourceUp->Height());
		_btnDown.SetSize(resourceDown->Width(), resourceDown->Height());
		_scrollBall.SetSize(resourceBall->Width(), resourceBall->Height());
		_modeChanged = false;
		_value = 0;
	}
}

void TrackBar::btnDown_Clicked(Object* sender, Libwui::Events::CursorEventArgs* args)
{
	_value++;
	DrawUpdate();
}

void TrackBar::btnUp_Clicked(Object* sender, Libwui::Events::CursorEventArgs* args)
{
	_value--;
	DrawUpdate();
}

void TrackBar::scollBall_held(Object* sender, Libwui::Events::CursorEventArgs* args)
{
	_scrollBallDrag = true;
}

void TrackBar::scrollBall_release(Object* sender, Libwui::Events::CursorEventArgs* args)
{
	_scrollBallDrag = false;
}

void TrackBar::scrollBall_move(Object* sender, Libwui::Events::CursorEventArgs* args)
{
	Device::PadController controller = args->Controller();

	if(controller.wpad.btns_h == 0)
		_scrollBallDrag = false;

	if(_scrollBallDrag)
	{
		if(_mode == TrackBarMode_Vertical)
		{
			int topPosition = controller.wpad.ir.y - _scrollBar.GetTop() - (_scrollBall.GetHeight() / 2);
			int yPosition;

			if(topPosition + _scrollBall.GetHeight() >= _scrollBar.GetHeight())
				yPosition = _scrollBar.GetHeight() - _scrollBall.GetHeight();
			else if(topPosition <= 0)
				yPosition = 0;
			else
				yPosition = topPosition;

			_scrollBall.SetPosition((_scrollBar.GetWidth() - _scrollBall.GetWidth()) / 2, yPosition);
		}
		else if(_mode == TrackBarMode_Vertical)
		{
			int leftPosition = controller.wpad.ir.x - _scrollBar.GetLeft() - (_scrollBall.GetWidth() / 2);
			int xPosition;

			if(leftPosition + _scrollBall.GetWidth() >= _scrollBar.GetWidth())
				xPosition = _scrollBar.GetWidth() - _scrollBall.GetWidth();
			else if(leftPosition <= 0)
				xPosition = 0;
			else
				xPosition = leftPosition;

			_scrollBall.SetPosition(xPosition, (_scrollBar.GetHeight() - _scrollBall.GetHeight()) / 2);
		}
		_scrollBallMoved = true;
		DrawUpdate();
	}
}

void TrackBar::SetValue(u32 val)
{
	if(InvokeRequired())
	{
		stringstream buffer;
		buffer << val;
		Message* m = new Message(_fullId, "Value", buffer.str());
		UIManager::AddMessage(m);
	}
	else
	{
		_value = val;
		DrawUpdate();
	}
}

void TrackBar::SetMinValue(u32 min)
{
	if(InvokeRequired())
	{
		stringstream buffer;
		buffer << min;
		Message* m = new Message(_fullId, "MinValue", buffer.str());
		UIManager::AddMessage(m);
	}
	else
	{
		_minValue = min;
		DrawUpdate();
	}
}

void TrackBar::SetMaxValue(u32 max)
{
	if(InvokeRequired())
	{
		stringstream buffer;
		buffer << max;
		Message* m = new Message(_fullId, "MaxValue", buffer.str());
		UIManager::AddMessage(m);
	}
	else
	{
		_maxValue = max;
		DrawUpdate();
	}
}

void TrackBar::SetMode(TrackBarMode mode)
{
	if(InvokeRequired())
	{
		stringstream params;
		params << (int)mode;
		Message* m = new Message(_fullId, "Mode", params.str());
		UIManager::AddMessage(m);
	}
	else
	{
		_mode = mode;
		_modeChanged = true;
		DrawUpdate();
	}
}

u32 TrackBar::GetValue()
{
	return _value;
}

u32 TrackBar::GetMinValue()
{
	return _minValue;
}

u32 TrackBar::GetMaxValue()
{
	return _maxValue;
}

TrackBarMode TrackBar::GetMode()
{
	return _mode;
}

void TrackBar::OnValueChanged()
{
	TrackBarEventArgs e(_value);
	ValueChanged(this, &e);
}

void TrackBar::DrawUpdate()
{
	float step = 0.0;
	if(_mode == TrackBarMode_Vertical)
		step = ((float)(_scrollBar.GetHeight() - 24)) / ((float)(_maxValue - _minValue));
	else if(_mode == TrackBarMode_Horizontal)
		step = ((float)(_scrollBar.GetWidth() - 24)) / ((float)(_maxValue - _minValue));
	if(_scrollBallMoved)
	{
		if(_mode == TrackBarMode_Vertical)
			_value = (_scrollBall.GetTop() - _scrollBar.GetTop()) / step;
		else if(_mode ==  TrackBarMode_Horizontal)
			_value = (_scrollBall.GetLeft() - _scrollBar.GetLeft()) / step;
	}
	if(_value <= _minValue)
	{
		_value = _minValue;
		_btnUp.Enabled(false);
		_btnDown.Enabled(true);
	}
	else if(_value  >= _maxValue)
	{
		_value = _maxValue;
		_btnUp.Enabled(true);
		_btnDown.Enabled(false);
	}
	else
	{
		_btnUp.Enabled(true);
		_btnDown.Enabled(true);
	}
	if(!_scrollBallMoved)
	{
		if(_mode == TrackBarMode_Vertical)
			_scrollBall.SetPosition(10, ((float)_value)* step);
		else if(_mode == TrackBarMode_Horizontal)
			_scrollBall.SetPosition(((float)_value)* step, 10);
	}
	_scrollBallMoved = false;
	OnValueChanged();
}

void TrackBar::UpDefaultImage(const std::string& imagePath)
{
	_btnUp.DefaultImage(imagePath);
}

std::string TrackBar::UpDefaultImage() const
{
	return _btnUp.DefaultImage();
}

void TrackBar::UpOverImage(const std::string& imagePath)
{
	_btnUp.OverImage(imagePath);
}

std::string TrackBar::UpOverImage() const
{
	return _btnUp.OverImage();
}

void TrackBar::UpClickedImage(const std::string& imagePath)
{
	_btnUp.ClickedImage(imagePath);
}

std::string TrackBar::UpClickedImage() const
{
	return _btnUp.ClickedImage();
}

void TrackBar::DownDefaultImage(const std::string& imagePath)
{
	_btnDown.DefaultImage(imagePath);
}

std::string TrackBar::DownDefaultImage() const
{
	return _btnDown.DefaultImage();
}

void TrackBar::DownOverImage(const std::string& imagePath)
{
	_btnDown.OverImage(imagePath);
}

std::string TrackBar::DownOverImage() const
{
	return _btnDown.OverImage();
}

void TrackBar::DownClickedImage(const std::string& imagePath)
{
	_btnDown.ClickedImage(imagePath);
}

std::string TrackBar::DownClickedImage() const
{
	return _btnDown.ClickedImage();
}

void TrackBar::ScrollBarImage(const std::string& imagePath)
{
	_scrollBar.ImageLocation(imagePath);
}

std::string TrackBar::ScrollBarImage() const
{
	return _scrollBar.ImageLocation();
}

void TrackBar::ScrollBallImage(const std::string& imagePath)
{
	_scrollBall.ImageLocation(imagePath);
}

std::string TrackBar::ScrollBallImage() const
{
	return _scrollBall.ImageLocation();
}
