#include <libwiisys.h>

using namespace Libwiisys::Exceptions;

AbortException::AbortException() :
	Exception("Process aborted.", -1) {
}

std::string AbortException::GetType()
{
	return "Libwiisys::Exceptions::AbortException,"+Exception::GetType();
}