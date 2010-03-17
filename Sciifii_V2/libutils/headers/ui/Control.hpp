#ifndef _UI_CONTROL_
#define _UI_CONTROL_

#include <string>
#include <set>

#include "Message.hpp"
#include "Device/PadControllers.hpp"
#include "../Object.h"
#include "../events/Event.h"
#include "Events/CursorEvent.h"

namespace UI
{
	typedef enum
	{
		VAlign_Top,
		VAlign_Bottom,
		VAlign_Middle
	} VAlign;
	
	typedef enum
	{
		HAlign_Left,
		HAlign_Right,
		HAlign_Center
	} HAlign;
	
	class Control : public Object
	{		
	protected:	
		std::string _fullId;
		HAlign _hAlign;
		VAlign _vAlign;
		int _xoffset;
		int _yoffset;
		int _width;
		int _height;
		bool _initialized;
		
		virtual void Draw();
		
		bool InvokeRequired();
		bool IsInside(int x, int y);
		virtual bool IsInUITree();
		
		virtual void SetId(const std::string& newId);
		virtual void OnCursorEnter();
		virtual void OnCursorLeave();
		virtual void OnCursorMove(Device::PadController &c);
		virtual void OnClick(Device::PadController &c);
		virtual void OnCursorButtonDown(Device::PadController &c);
		virtual void OnCursorButtonUp(Device::PadController &c);
		
	public:
		Control();
		virtual void InitializeComponents();
		
		virtual void AddChildren(Control* child);
		virtual void RemoveChildren(Control* child);
		void StartDrawing();
		
		void BackgroundColor(GXColor color);
		GXColor BackgroundColor() const;
		
		void BackgroundImage(const std::string& image);
		std::string BackgroundImage() const;
		
		
		int GetLeft();
		int GetTop();
		int GetWidth();
		int GetHeight();
		
		void HorizontalAlignement(HAlign alignement);
		HAlign HorizontalAlignement() const;
		
		Control* Parent();
		virtual void ProcessInput(Device::PadController& controller);
		virtual void ProcessMessage(Message& message);
		void SetPosition(int x, int y);
		void SetSize(int w, int h);
		
		void VerticalAlignement(VAlign alignement);
		VAlign VerticalAlignement() const;
		
		bool Visible() const;
		void Visible(bool visibility);
		
		bool Enabled() const;
		void Enabled(bool enabled);
		
		virtual ~Control();
		
		Event CursorEnter;
		Event CursorLeave;
		Events::CursorEvent CursorMove;
		Events::CursorEvent Click;
		Events::CursorEvent CursorButtonDown;
		Events::CursorEvent CursorButtonUp;
		
	private:
		static const u64 STATE_VISIBLE = 0x1;
		static const u64 STATE_OVER = 0x2;
		static const u64 STATE_CLICKED = 0x4;
		static const u64 STATE_ENABLED = 0x8;
		
		u64 _idGenerator;
		std::set<Control*> _childs;
		Control* _parent;
		u64 _state;
		u32 _buttonState;
		u32 _downButton;
		GXColor _backgroundColor;
		std::string _backgroundImage;
		
		void ApplyState(u64 stateMask);
		void RemoveState(u64 stateMask);
		bool IsStateActive(u64 stateMask) const;
	};
}

#endif