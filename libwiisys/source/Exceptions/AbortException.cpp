#include <libwiisys.h>

using namespace Libwiisys::Exceptions;

AbortException::AbortException() :
	Exception("Process aborted.", -1) {
}
