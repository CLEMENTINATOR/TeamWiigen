#ifndef _MENU_ITEM_H_
#define _MENU_ITEM_H_

#include <string>
#include <libwiisys.h>
#include "../Events/OptionEvent.h"
#include "../Events/OptionEventArgs.h"

class MenuItem : public Libwiisys::Object
{	
protected:
	std::string _text;
	void OnModifyOption(OptionEventArgs& args);
	
public:
	bool Selectable;
	bool Selected;
	
	MenuItem(TiXmlElement* node);
	virtual void Render() = 0;
	virtual void ButtonPressed(u32 button);
	virtual void Validate();
	virtual void Cancel();
	
	OptionEvent OptionSelectionChanged;
};

#endif