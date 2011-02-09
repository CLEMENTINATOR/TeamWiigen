#include <sciifii/business/common/ExitSciifiiException.h>

using namespace Libwiisys::Exceptions;

ExitSciifiiException::ExitSciifiiException()
  : Exception("End of sciifii execution requested!")
{}
