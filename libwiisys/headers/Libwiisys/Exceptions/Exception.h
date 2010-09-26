#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include <string>
#include <ogcsys.h>
#include "../Object.h"

/*! \namespace Libwiisys::Exceptions
 *
 * \brief Exceptions used in Libwiisys
 */
namespace Libwiisys {namespace Exceptions {

		/*! \class Exception
		 * \brief Simple exception class
		 * \author Arasium, Teton, Fanta
		 * \version 1.0
		 *
		 * The Exception class allow the user to create & catch "custom" Exceptions
		 * This class must be the base class of all other exceptions. This will allow e better
		 * tracking of errors.
		 */
		class Exception : public Object
		{
		public:
			virtual std::string GetType();
			/*!
			 * \brief Constructor
			 * \param message The message text of your exception
			 * \param errorCode The error code associated to the exception
			 */
			Exception(const std::string& message, s32 errorCode);

			/*!
			 * \brief Return the exception message
			 * \return The exception message
			 */
			std::string GetMessage();

			/*!
			 * \brief Return the exception error code
			 * \return The exception error code
			 */
			s32 GetCode();

		private:
			std::string _message;
			s32 _errorCode;
		};

	}}

#endif
