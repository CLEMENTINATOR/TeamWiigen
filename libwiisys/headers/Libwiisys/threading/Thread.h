#ifndef _UTILS_THREAD_H_
#define _UTILS_THREAD_H_

#include <fastdelegate.h>
#include "../Object.h"
#include <ogcsys.h>

/*! \namespace Libwiisys::Threading
 * \brief Object oriented Thread system
 */
namespace Libwiisys {
	namespace Threading {
		/**
		 * \class Thread
		 * \brief Manage and create thread easily
		 *
		 * This class is used for multithreading in your programs
		 */
		class Thread : public Object
		{
		public:
			/** Simple typedef for a more readable code :)*/
			typedef fastdelegate::FastDelegate1<Object *> ThreadStart;

			/**
			 *\brief Constructor
			 */
			Thread(ThreadStart start);

			/**
			 * \brief Start the thread
			 * \param params the parameters which are given to the thread
			 */
			void Start(Object* params = NULL);

		private:
			lwp_t _threadId;
			ThreadStart _start;
			Object* _params;

		protected:

			/**
			 * \brief Run the thread
			 */
			void Run();

			/**
			 * \brief Get the entry point and run the thread
			 * \param pthis a pointer on this thread
			 */
			static void * EntryPoint(void* pthis);
		};
	}
}
#endif
