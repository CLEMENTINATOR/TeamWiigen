#include <libwiisys.h>

using namespace Libwiisys::Exceptions;

/**
 *\brief Constructor, exception with default message, this doesn't abort the process if not handled in try-catch
 */
AbortException::AbortException() : Exception("Process aborted.", -1) {}
