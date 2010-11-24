#include <Libwiisys/Exceptions/AbortException.h>

using namespace Libwiisys::Exceptions;

AbortException::AbortException() :
    Exception("Process aborted.")
{}

std::string AbortException::GetType()
{
  return "Libwiisys::Exceptions::AbortException,"+Exception::GetType();
}
