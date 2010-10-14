#ifndef DOWORKEVENT_H_
#define DOWORKEVENT_H_
#include "Thread.h"
namespace Libwiisys
{

  namespace Threading
  {
    class DoWorkEvent : public Object
    {
      public:
        typedef fastdelegate::FastDelegate2<Object*, Object*> DelegateType;
        virtual void operator()(Object* sender, Object* args);
        virtual void operator+=(DelegateType listener);
        virtual void operator-=(DelegateType listener);
      private:
        std::list<DelegateType> listenerList; // pointer to object
        Thread* th;

    };

  }

}

#endif /* DOWORKEVENT_H_ */
