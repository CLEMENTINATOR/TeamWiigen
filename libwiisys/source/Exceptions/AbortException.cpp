#include <libwiisys.h>

using namespace Libwiisys::Exceptions;

/**
 *\brief Default Constructor
 *
 * This will create the base Exception with a default error code and message.
 */
AbortException::AbortException() : Exception("Process aborted.", -1) {}
