#ifndef _NAVIGATE_EVENT_ARGS_H_
#define _NAVIGATE_EVENT_ARGS_H_

#include <string>
#include <libwiisys.h>

class NavigateEventArgs : public Libwiisys::Object
{
public:
	std::string NavigateTo;
	std::string MenuId;
	bool ValidateCurrentMenu;
};

#endif