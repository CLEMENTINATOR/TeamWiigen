#ifndef _PROGRESSEVENTARGS_H_
#define _PROGRESSEVENTARGS_H_

#include <string>
#include <gctypes.h>
#include <libwiisys.h>




class ProgressEventArgs : public Libwiisys::EventArgs
{
public:
	std::string message;
	f32 percent;
};

#endif
