#ifndef _G_MEMORY_VIEWER_
#define _G_MEMORY_VIEWER_

#include <Libwiisys/Object.h>
#include <Libwui/Component/Button.hpp>

class GMemoryViewer : public Libwui::Control
{
private:
	Libwui::Component::Button btnView;
	Libwui::Component::Label view;
	Libwui::Component::Label diff;
	
public:
	GMemoryViewer();
  void InitializeComponents();
	void DisplayMemory(Object* sender, Libwui::Events::CursorEventArgs* args);
};

#endif