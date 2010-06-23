#include <exception/Exception.h>

using namespace std;
using namespace Libwiisys;

/*!
* \brief Constructor
* \param message The message text of your exception
* \param errorCode The error code associated to the exception
*/
Exception::Exception(string message, s32 errorCode)
{
	_message = message;
	_errorCode = errorCode;
}

/*!
* \brief Return the exception message
* \return The exception message
*/
string Exception::GetMessage()
{
	return _message;
}

/*!
* \brief Return the exception error code
* \return The exception error code
*/
s32 Exception::GetCode()
{
	return _errorCode;
}
