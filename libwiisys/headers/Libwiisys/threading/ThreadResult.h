#ifndef _THREADRESULT_H_
#define _THREADRESULT_H_

#include <FastDelegate.h>
#include "../Object.h"
#include <ogcsys.h>


namespace Libwiisys
{
  namespace Threading
  {

    class ThreadResult : public Object
    {
      public:
        bool HasError;
        void* Result;
    };
  }
}
#endif
