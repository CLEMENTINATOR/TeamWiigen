#ifndef _TITLEEVENTS_H_
#define _TITLEEVENTS_H_

#include <ogcsys.h>
#include "EventArgs.h"
#include "../com/Buffer.h"

class TitleEventArgs : public EventArgs
{
public:
	Buffer buffer;
	tmd_content* tmdInfo;
	bool skipStep;
	bool abortProcess;
};

#endif
