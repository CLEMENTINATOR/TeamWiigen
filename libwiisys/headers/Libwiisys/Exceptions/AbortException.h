#ifndef ABORTEXCEPTION_H_
#define ABORTEXCEPTION_H_

#include "Exception.h"

namespace Libwiisys {namespace Exceptions {

		/*!
		 * \class AbortException
		 * \brief Used to stop a process
		 * \author Arasium, Teton, Fanta
		 * \version 1.0
		 *
		 * Actually, this exceptions is only used during Title installation.
		 * If an AbortException is thrown, the installation will stop, but the
		 * program will continue.
		 */
		class AbortException : public Exception
		{
		public:
			/**
			 * \brief Default Constructor
			 *
			 * This will create the base Exception with a default error code and message.
			 */
			AbortException();

		};

	}}

#endif
