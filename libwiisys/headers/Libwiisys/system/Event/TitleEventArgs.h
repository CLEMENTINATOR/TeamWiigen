#ifndef _TITLEEVENTS_H_
#define _TITLEEVENTS_H_

#include <ogcsys.h>
#include "../../EventArgs.h"
#include "../../Buffer.h"

namespace Libwiisys { namespace System { namespace Event {
/**
 * \class TitleEventArgs
 * \brief Events args used in Title Installation
 * \see TitleEvent
 */
class TitleEventArgs : public EventArgs
{
public:
	Buffer buffer;
	tmd_content* tmdInfo;
	bool skipStep;
	bool abortProcess;
};

}}}

#endif
