#include <ui/Control.hpp>

#include <sstream>

#include <ui/video.h>
#include <ui/UIManager.hpp>
#include <ui/Resources/ImageResourceManager.hpp>

using namespace UI;
using namespace UI::Resources;
using namespace UI::Events;
using namespace UI::Device;
using namespace std;

Control::Control()
: _fullId(),
  _hAlign(HAlign_Left),
  _vAlign(VAlign_Top),
  _xoffset(0),
  _yoffset(0),
  _width(0),
  _height(0),
  _initialized(false),
  _idGenerator(1),
  _childs(),
  _parent(NULL),
  _state(STATE_ENABLED | STATE_VISIBLE),
  _buttonState(0),
  _downButton(0),
  _backgroundColor((GXColor){255,255,255,0}),
  _backgroundImage()
{}

void Control::AddChildren(Control* child)
{
  if(InvokeRequired())
  {
	stringstream params;
	params << (void*)child;
	Message* m = new Message(_fullId, "AddChildren", params.str());
	UIManager::AddMessage(m);
  }
  else
  {
	if(child->_parent != NULL)
	{
	  Control* parent = child->_parent;
	  parent->_childs.erase(child);
	}

	_childs.insert(child);
	stringstream childId;
	childId << _fullId << "_" << _idGenerator++;
	child->SetId(childId.str());
	child->_parent = this;

	if(_initialized  && !child->_initialized)
		child->InitializeComponents();
  }
}

void Control::InitializeComponents()
{
	if(!_initialized)
	{
		for(set<Control*>::iterator child = _childs.begin(); child != _childs.end(); child++)
			if(!(*child)->_initialized)
				(*child)->InitializeComponents();

		_initialized = true;
	}
}

void Control::ApplyState(u64 stateMask)
{
	_state |= stateMask;
}

void Control::RemoveState(u64 stateMask)
{
	_state &= ~stateMask;
}

bool Control::IsStateActive(u64 stateMask) const
{
	return (_state & stateMask);
}

void Control::RemoveChildren(Control* child)
{
  if(InvokeRequired())
  {
	stringstream params;
	params << (void*)child;
	Message* m = new Message(_fullId, "RemoveChildren", params.str());
	UIManager::AddMessage(m);
  }
  else if(child->_parent == this)
  {
	child->_parent = NULL;
	_childs.erase(child);
  }
}

void Control::Draw()
{
	for(set<Control*>::iterator child = _childs.begin(); child != _childs.end(); child++)
		(*child)->StartDrawing();
}

void Control::StartDrawing()
{
	if(!Visible())
		return;
    if(_backgroundImage!="")
    {
        ImageResource* back = ImageResourceManager::Get(_backgroundImage);
        if(back != NULL)
            Menu_DrawImg(GetLeft(), GetTop(), back->Width(), back->Height(), back->Image(), 0, 1, 1, 255);
        else
            Menu_DrawRectangle(GetLeft(), GetTop(), GetWidth(), GetHeight(), _backgroundColor, 1);
    }

	Draw();
}

int Control::GetLeft()
{
	int x = 0;
	int pWidth = 0;
	int pLeft = 0;

	if(_parent)
	{
		pWidth = _parent->GetWidth();
		pLeft = _parent->GetLeft();
	}

	/*if(effects & (EFFECT_SLIDE_IN | EFFECT_SLIDE_OUT))
		pLeft += xoffsetDyn;*/

	switch(_hAlign)
	{
		case HAlign_Left:
			x = pLeft;
			break;
		case HAlign_Center:
			x = pLeft + (pWidth/2) - (_width/2);
			break;
		case HAlign_Right:
			x = pLeft + pWidth - _width;
			break;
	}

	return x + _xoffset;
}

int Control::GetTop()
{
	int y = 0;
	int pHeight = 0;
	int pTop = 0;

	if(_parent)
	{
		pHeight = _parent->GetHeight();
		pTop = _parent->GetTop();
	}

	/*if(effects & (EFFECT_SLIDE_IN | EFFECT_SLIDE_OUT))
		pTop += yoffsetDyn;*/

	switch(_vAlign)
	{
		case VAlign_Top:
			y = pTop;
			break;
		case VAlign_Middle:
			y = pTop + (pHeight/2) - (_height/2);
			break;
		case VAlign_Bottom:
			y = pTop + pHeight - _height;
			break;
	}
	return y + _yoffset;
}

int Control::GetWidth()
{
	return _width;
}

int Control::GetHeight()
{
	return _height;
}

void Control::HorizontalAlignement(HAlign alignement)
{
	if(InvokeRequired())
	{
		stringstream params;
		params << (int)alignement;
		Message* m = new Message(_fullId, "HorizontalAlignement", params.str());
		UIManager::AddMessage(m);
	}
	else
		_hAlign = alignement;
}

HAlign Control::HorizontalAlignement() const
{
	return _hAlign;
}

bool Control::InvokeRequired()
{
	if(!IsInUITree())
		return false;

	return !UIManager::IsUiThread();
}

bool Control::IsInside(int x, int y)
{
	if(x > this->GetLeft() && x < (this->GetLeft() + _width)
	&& y > this->GetTop() && y < (this->GetTop() + _height))
		return true;
	return false;
}

bool Control::IsInUITree()
{
	if(_parent == NULL)
		return false;
	else
		return _parent->IsInUITree();
}

Control* Control::Parent()
{
	return _parent;
}

void Control::ProcessMessage(Message& message)
{
	//Si le message n'est pas pour cette branche de composants
	if(message.GetComponentId().find(_fullId) == string::npos)
		return;

	//Si le message n'est pas pour moi, il est pour un enfant
	if(message.GetComponentId() != _fullId)
	{
		for(set<Control*>::iterator child = _childs.begin(); child != _childs.end(); child++)
			(*child)->ProcessMessage(message);
		return;
	}

	//Sinon, il est pour moi
	string tag = message.GetTag();
	stringstream params(message.GetSerializedParameters());

	if(tag == "AddChildren")
	{
		void* child;
		params >> child;
		AddChildren((Control*)child);
	}
	else if(tag == "RemoveChildren")
	{
		void* child;
		params >> child;
		RemoveChildren((Control*)child);
	}
	else if(tag == "SetSize")
	{
		int w, h;
		params >> w >> h;
		SetSize(w, h);
	}
	else if(tag == "SetPosition")
	{
		int x, y;
		params >> x >> y;
		SetPosition(x, y);
	}
	else if(tag == "HorizontalAlignement")
	{
		int align;
		params >> align;
		HorizontalAlignement((HAlign)align);
	}
	else if(tag == "VerticalAlignement")
	{
		int align;
		params >> align;
		VerticalAlignement((VAlign)align);
	}
	else if(tag == "Visible")
	{
		bool visible;
		params >> visible;
		Visible(visible);
	}
	else if(tag == "Enabled")
	{
		bool enabled;
		params >> enabled;
		Enabled(enabled);
	}
	else if(tag == "BackgroundColor")
	{
		u8 r,g,b,a;
		params >> r >> g >> b >> a;
		BackgroundColor((GXColor) { r, g, b, a});
	}
	else if(tag == "BackgroundImage")
		BackgroundImage(params.str());
}

void Control::ProcessInput(PadController& controller)
{
	if(controller.wpad.ir.valid)
	{
		if(IsInside(controller.wpad.ir.x, controller.wpad.ir.y))
		{
			//On entre dans le control
			if(!IsStateActive(STATE_OVER))
			{
				OnCursorEnter();
				if(controller.wpad.btns_h > 0)
				{
					ApplyState(STATE_CLICKED);
					_downButton = _downButton | controller.wpad.btns_h;
				}
			}
			ApplyState(STATE_OVER);
			OnCursorMove(controller);
		}
		else
		{
			if(IsStateActive(STATE_OVER))
				OnCursorLeave();
			RemoveState(STATE_OVER);
			RemoveState(STATE_CLICKED);
			_buttonState = 0;
			_downButton = 0;
		}
	}

	//button down
	if(IsStateActive(STATE_OVER)
	   && Visible()
	   && Enabled()
	   && controller.wpad.btns_d > 0)
	{
		ApplyState(STATE_CLICKED);
		OnCursorButtonDown(controller);
		_buttonState = _buttonState | controller.wpad.btns_d;
		_downButton = _downButton | controller.wpad.btns_d;
	}

	//button up & click
	if(IsStateActive(STATE_OVER)
	   && Visible()
	   && Enabled()
	   && controller.wpad.btns_u > 0)
	{
		u32 justReleasedButtons = _downButton & controller.wpad.btns_u;
		if(justReleasedButtons > 0)
		{
			u32 clickedButton = _buttonState & justReleasedButtons;
			if(clickedButton > 0)
			{
				controller.btns_c = clickedButton;
				OnClick(controller);
				_buttonState = _buttonState & (0xFFFFFFFF - clickedButton);
			}

			OnCursorButtonUp(controller);
			_downButton = _downButton & (0xFFFFFFFF - justReleasedButtons);
		}

		if(_downButton == 0)
			RemoveState(STATE_CLICKED);
	}

	for(set<Control*>::iterator child = _childs.begin(); child != _childs.end(); child++)
		(*child)->ProcessInput(controller);
}

void Control::SetId(const string& newId)
{
	_idGenerator = 1;
	_fullId = newId;

	for(set<Control*>::iterator childIte = _childs.begin(); childIte != _childs.end(); childIte++)
	{
		stringstream childId;
		childId << _fullId << "_" << _idGenerator++;
		(*childIte)->SetId(childId.str());
	}
}

void Control::SetPosition(int x, int y)
{
	if(InvokeRequired())
	{
		stringstream params;
		params << x << " " << y;
		Message* m = new Message(_fullId, "SetPosition", params.str());
		UIManager::AddMessage(m);
	}
	else
	{
		_xoffset = x;
		_yoffset = y;
	}
}

void Control::SetSize(int w, int h)
{
	if(InvokeRequired())
	{
		stringstream params;
		params << w << " " << h;
		Message* m = new Message(_fullId, "SetSize", params.str());
		UIManager::AddMessage(m);
	}
	else
	{
		_width = w;
		_height = h;
	}
}

void Control::VerticalAlignement(VAlign alignement)
{
	if(InvokeRequired())
	{
		stringstream params;
		params << (int)alignement;
		Message* m = new Message(_fullId, "VerticalAlignement", params.str());
		UIManager::AddMessage(m);
	}
	else
		_vAlign = alignement;
}

VAlign Control::VerticalAlignement() const
{
	return _vAlign;
}

Control::~Control()
{
	for(set<Control*>::iterator child = _childs.begin(); child != _childs.end(); child++)
		(*child)->_parent = NULL;

	if(_parent != NULL)
	  _parent->_childs.erase(this);

	_parent = NULL;
}

void Control::Visible(bool visibility)
{
	if(InvokeRequired())
	{
		stringstream argStream;
		argStream << visibility;
		Message* m = new Message(_fullId, "Visible", argStream.str());
		UIManager::AddMessage(m);
		return;
	}

	if(visibility)
		ApplyState(STATE_VISIBLE);
	else
		RemoveState(STATE_VISIBLE);
}

bool Control::Visible() const
{
	if(_state & STATE_VISIBLE)
	{
		if(_parent == NULL)
			return true;
		else
			return _parent->Visible();
	}
	return false;
}

void Control::Enabled(bool enable)
{
	if(InvokeRequired())
	{
		stringstream argStream;
		argStream << enable;
		Message* m = new Message(_fullId, "Enabled", argStream.str());
		UIManager::AddMessage(m);
		return;
	}

	if(enable)
		ApplyState(STATE_ENABLED);
	else
		RemoveState(STATE_ENABLED);
}

bool Control::Enabled() const
{
	if(IsStateActive(STATE_ENABLED))
	{
		if(_parent == NULL)
			return true;
		else
			return _parent->Enabled();
	}
	else
		return false;
}

void Control::BackgroundColor(GXColor color)
{
	if(InvokeRequired())
	{
		stringstream argStream;
		argStream << color.r << " " << color.g << " " << color.b << " " << color.a;
		Message* m = new Message(_fullId, "BackgroundColor", argStream.str());
		UIManager::AddMessage(m);
		return;
	}
	else
		_backgroundColor = color;
}

GXColor Control::BackgroundColor() const
{
	return _backgroundColor;
}

void Control::BackgroundImage(const string& image)
{
	if(InvokeRequired())
	{
		Message* m = new Message(_fullId, "BackgroundImage", image);
		UIManager::AddMessage(m);
		return;
	}
	else
	{
		_backgroundColor = (GXColor){255,255,255,0};
		_backgroundImage = image;
	}
}

string Control::BackgroundImage() const
{
	return _backgroundImage;
}

void Control::OnCursorEnter()
{
	EventArgs e;
	CursorEnter(this, &e);
}

void Control::OnCursorLeave()
{
	EventArgs e;
	CursorLeave(this, &e);
}

void Control::OnCursorMove(Device::PadController &c)
{
	CursorEventArgs e(c);
	CursorMove(this, &e);
}

void Control::OnClick(Device::PadController &c)
{
	CursorEventArgs e(c);
	Click(this, &e);
}

void Control::OnCursorButtonDown(Device::PadController &c)
{
	CursorEventArgs e(c);
	CursorButtonDown(this, &e);
}

void Control::OnCursorButtonUp(Device::PadController &c)
{
	CursorEventArgs e(c);
	CursorButtonUp(this, &e);
}
