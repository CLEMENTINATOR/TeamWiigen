#ifndef _OPTION_EVENT_ARGS_H_
#define _OPTION_EVENT_ARGS_H_

#include <ogcsys.h>
#include <libwiisys.h>
#include "../../../Option.h"

class OptionEventArgs : public Libwiisys::EventArgs
{
public:
	bool Incremental;
	std::vector<Option> Options;
};

#endif
