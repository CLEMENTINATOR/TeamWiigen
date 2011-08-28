#ifndef _UTILS_THREAD_H_
#define _UTILS_THREAD_H_

#include <FastDelegate.h>
#include "../Object.h"
#include "ThreadResult.h"
#include "ThreadResultEvent.h"
#include <ogcsys.h>

/*! \namespace Libwiisys::Threading
 * \brief Object oriented Thread system
 */
namespace Libwiisys
{
  namespace Threading
  {
    /**
     * \class Thread
     * \brief Manage and create thread easily
     *
     * This class is used for multithreading in your programs
     */
    class Thread : public Object
    {
      public:
        virtual std::string GetType();

        /** Simple typedef for a more readable code :)*/
        typedef fastdelegate::FastDelegate1<Object *, void*> ThreadStart;

        /**
         *\brief Constructor
         */
        Thread(ThreadStart start);
        ~Thread();
        /**
         * \brief Start the thread
         * \param params the parameters which are given to the thread
         */
        void Start(Object* params = NULL);

        void Suspend();
        void Resume();
        void* Join();
		
		static void SuspendOtherThreads();
		static void ResumeOtherThreads();

        ThreadResultEvent ThreadTerminated;

      private:
        lwp_t _threadId;
        ThreadStart _start;
        Object* _params;
        ThreadResult _threadResult;

      protected:

        /**
         * \brief Run the thread
         */
        void* Run();

        /**
         * \brief Get the entry point and run the thread
         * \param pthis a pointer on this thread
         */
        static void * EntryPoint(void* pthis);
    };
  }
}
#endif
