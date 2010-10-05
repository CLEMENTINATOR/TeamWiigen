#ifndef _MENU_ITEM_H_
#define _MENU_ITEM_H_

#include <string>
#include <libwiisys.h>
#include "../Events/OptionEvent.h"
#include "../Events/OptionEventArgs.h"
#include "../Events/NavigateEvent.h"
#include "../Events/NavigateEventArgs.h"

class MenuItem : public Libwiisys::Object
{	
protected:
	std::string _text;
	void OnModifyOption(OptionEventArgs& args);
	void OnNavigate(NavigateEventArgs& args);
	
public:
	bool Selectable;
	bool Selected;
	
	MenuItem(TiXmlElement* node);
	virtual void Render() = 0;
	virtual void ButtonPressed(u32 button);
	virtual void Validate();
	virtual void Cancel();
	
	OptionEvent OptionSelectionChanged;
	NavigateEvent NavigateRequested;
};

#endif