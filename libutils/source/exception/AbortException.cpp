#include <AbortException.h>

using namespace Libwiisys;

 AbortException::AbortException() : Exception("Process aborted.", -1) {}
