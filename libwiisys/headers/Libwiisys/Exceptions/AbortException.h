#ifndef ABORTEXCEPTION_H_
#define ABORTEXCEPTION_H_

#include "Exception.h"

namespace Libwiisys { namespace Exceptions {

class AbortException : public Exception
{
public:
	AbortException();
};

}}


#endif
