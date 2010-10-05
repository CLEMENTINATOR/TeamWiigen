#ifndef _MENU_ITEM_H_
#define _MENU_ITEM_H_

#include <string>
#include <libwiisys.h>
#include "../Events/SwitchEvent.h"
#include "../Events/SwitchEventArgs.h"
#include "../Events/NavigateEvent.h"
#include "../Events/NavigateEventArgs.h"

class MenuItem : public Libwiisys::Object
{	
protected:
	std::string _text;
	void OnModifySwitch(SwitchEventArgs& args);
	void OnNavigate(NavigateEventArgs& args);
	
public:
	bool Selectable;
	bool Selected;
	
	MenuItem(TiXmlElement* node);
	virtual void Render() = 0;
	virtual void ButtonPressed(u32 button);
	virtual void Validate();
	virtual void Cancel();
	
	SwitchEvent SwitchSelectionChanged;
	NavigateEvent NavigateRequested;
};

#endif