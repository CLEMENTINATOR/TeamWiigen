#include <sciifii/business/Common/ExitSciifiiException.h>

using namespace Libwiisys::Exceptions;

ExitSciifiiException::ExitSciifiiException()
  : Exception("End of sciifii execution requested!")
{}