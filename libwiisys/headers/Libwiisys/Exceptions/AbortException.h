#ifndef ABORTEXCEPTION_H_
#define ABORTEXCEPTION_H_

#include "Exception.h"

namespace Libwiisys { namespace Exceptions {

/*!
 * \class AbortException
 * \brief AbortException class
 * \author Arasium, Teton, Fanta
 * \version 1.0
 */
class AbortException : public Exception
{
public:
	AbortException();
};

}}


#endif
