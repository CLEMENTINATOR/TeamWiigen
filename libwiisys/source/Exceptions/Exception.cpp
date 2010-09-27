#include <libwiisys.h>

using namespace std;
using namespace Libwiisys::Exceptions;

Exception::Exception(const string& message) 
  :  _message(message)
{}

string Exception::GetMessage() {
	return _message;
}

string Exception::GetType()
{
	return "Libwiisys::Exceptions::Exception," + Object::GetType();	
}

string Exception::ToString()
{
	return "Exception: " + _message;	
}
