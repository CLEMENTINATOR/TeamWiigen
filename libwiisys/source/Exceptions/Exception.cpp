#include <libwiisys.h>

using namespace std;
using namespace Libwiisys::Exceptions;

Exception::Exception(const string& message, s32 errorCode) {
	_message = message;
	_errorCode = errorCode;
}

string Exception::GetMessage() {
	return _message;
}

s32 Exception::GetCode() {
	return _errorCode;
}
