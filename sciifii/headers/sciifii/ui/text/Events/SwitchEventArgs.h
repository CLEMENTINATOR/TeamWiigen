#ifndef _SWITCH_EVENT_ARGS_H_
#define _SWITCH_EVENT_ARGS_H_

#include <ogcsys.h>
#include <libwiisys.h>
#include "../../../Switch.h"

class SwitchEventArgs : public Libwiisys::EventArgs
{
public:
	bool Incremental;
	std::vector<Switch> Switches;
};

#endif
