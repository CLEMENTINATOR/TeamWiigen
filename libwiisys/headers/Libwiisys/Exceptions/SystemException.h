#ifndef _SYSTEM_EXCEPTION_H_
#define _SYSTEM_EXCEPTION_H_

#include <string>
#include <ogcsys.h>
#include "Exception.h"


namespace Libwiisys { namespace Exceptions {

		/*! \class SystemException
		 * \brief This is an exception thrown by the libogc (detected via ret code < 0)
		 * \author Arasium, Teton, Fanta
		 * \version 1.0
		 */
		class SystemException : public Exception
		{
		public:
			virtual std::string GetType();
			
			/*!
			 * \brief Constructor
			 * \param message The message text of your exception
			 * \param errorCode The error code associated to the exception
			 */
			SystemException(const std::string& message, s32 errorCode);

			/*!
			 * \brief Return the exception error code
			 * \return The exception error code
			 */
			s32 GetCode();
			
			virtual std::string ToString();

		private:
			s32 _errorCode;
		};

	}}

#endif
