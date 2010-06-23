#ifndef _UTILS_THREAD_H_
#define _UTILS_THREAD_H_

#include <fastdelegate.h>
#include "../Object.h"
#include <ogcsys.h>
namespace Libwiisys {
	namespace Threading{
class Thread : public Object
{
   public:
	  typedef fastdelegate::FastDelegate1<Object *> ThreadStart;
	  Thread(ThreadStart start);
      void Start(Object* params = NULL);

   private:
      lwp_t _threadId;
	  ThreadStart _start;
	  Object* _params;

   protected:
      void Run();
      static void * EntryPoint(void*);
};
	}
}
#endif
