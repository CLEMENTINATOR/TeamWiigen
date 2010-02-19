#ifndef _PROGRESSEVENTARGS_H_
#define _PROGRESSEVENTARGS_H_

#include <string>
#include <gctypes.h>

#include <libutils/events/EventArgs.h>

class ProgressEventArgs : public EventArgs
{
public:
	std::string message;
	f32 percent;
};

#endif
