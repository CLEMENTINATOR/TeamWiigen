#include <exception/AbortException.h>

 AbortException::AbortException() : Exception("Process aborted.", -1) {}
