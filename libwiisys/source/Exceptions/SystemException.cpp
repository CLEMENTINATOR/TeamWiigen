#include <libwiisys.h>

using namespace std;
using namespace Libwiisys::Exceptions;

SystemException::SystemException(const string& message, s32 errorCode) 
  : Exception(message),
	  _errorCode(errorCode)
{}

s32 SystemException::GetCode() {
	return _errorCode;
}

std::string SystemException::GetType()
{
	return "Libwiisys::Exceptions::SystemException," + Exception::GetType();	
}

string SystemException::ToString()
{
	stringstream str;
	str << "Exception (" << _errorCode << "): " << GetMessage();
	return str.str();
}
