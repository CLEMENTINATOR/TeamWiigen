#ifndef _THREAD_RESULT_EVENT_ARGS_H_
#define _THREAD_RESULT_EVENT_ARGS_H_

#include "ThreadResult.h"
#include "../EventArgs.h"
#include <ogcsys.h>


namespace Libwiisys
{
  namespace Threading
  {

    class ThreadResultEventArgs : public EventArgs
    {
      public:
        ThreadResultEventArgs(ThreadResult r, u32 tid);
        ThreadResult Result;
        u32 ThreadId;
    };
  }
}
#endif
