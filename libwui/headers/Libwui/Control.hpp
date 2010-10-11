#ifndef _UI_CONTROL_
#define _UI_CONTROL_

#include <string>
#include <set>

#include "Message.hpp"
#include "Device/PadControllers.hpp"
#include <libwiisys.h>

#include "Events/CursorEvent.h"

namespace Libwui
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
	
	class Control : public Libwiisys::Object
	{		
	protected:	
		std::string _fullId;
		HAlign _hAlign;
		VAlign _vAlign;
		s32 _xoffset;
		s32 _yoffset;
		s32 _width;
		s32 _height;
		bool _initialized;
		bool _invalidated;
		
		virtual void Draw();
		virtual void Invalidate();
		virtual void EnsureItems();
		
		bool InvokeRequired();
		bool IsInside(s32 x, s32 y);
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
		
		virtual void BackgroundColor(GXColor color);
		GXColor BackgroundColor() const;
		
		virtual void BackgroundImage(const std::string& image);
		std::string BackgroundImage() const;
		
		
		s32 GetLeft();
		s32 GetTop();
		s32 GetWidth();
		s32 GetHeight();
		
		virtual void HorizontalAlignement(HAlign alignement);
		HAlign HorizontalAlignement() const;
		
		virtual Control* Parent();
		virtual void ProcessInput(Device::PadController& controller);
		virtual void ProcessMessage(Message& message);
		void SetPosition(s32 x, s32 y);
		virtual void SetSize(s32 w, s32 h);
		
		virtual void VerticalAlignement(VAlign alignement);
		VAlign VerticalAlignement() const;
		
		virtual bool Visible() const;
		void Visible(bool visibility);
		
		bool Enabled() const;
		virtual void Enabled(bool enabled);
		
		virtual ~Control();
		
		Libwiisys::Event CursorEnter;
		Libwiisys::Event CursorLeave;
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
