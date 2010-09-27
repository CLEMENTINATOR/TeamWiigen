#ifndef _TITLEEVENTS_H_
#define _TITLEEVENTS_H_

#include <ogcsys.h>
#include "../../EventArgs.h"
#include "../../Buffer.h"

namespace Libwiisys {
	namespace System {
		namespace Event {
			/**
			 * \class TitleEventArgs
			 * \brief Events args used in Title Installation
			 * \see TitleEvent
			 */
			class TitleEventArgs : public EventArgs
			{
			public:
			
				virtual std::string GetType();
			
				/** Buffer accessible in your events functions*/
				Buffer buffer;

				/** tmd_content accessible in your events functions*/
				tmd_content* tmdInfo;

				/** flag accessible in your events functions; if set to true, i'll skip the actual step ( associated to the event )*/
				bool skipStep;

				/** flag accessible in your events functions; if set to true, i'll abort the title installation atm the event is called*/
				bool abortProcess;
			};

		}}}

#endif
