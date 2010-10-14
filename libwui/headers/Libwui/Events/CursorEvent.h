#ifndef _UI_EVENTS_CURSOREVENT_H_
#define _UI_EVENTS_CURSOREVENT_H_

#include <libwiisys/Object.h>

#include "CursorEventArgs.h"
#include <list>
#include <FastDelegate.h>

namespace Libwui
{
  namespace Events
  {
    class CursorEvent : public Libwiisys::Object
    {
      public:
        typedef fastdelegate::FastDelegate2<Object*,CursorEventArgs*> DelegateType;
        virtual void operator()(Object* sender, CursorEventArgs* args);
        virtual void operator+= (DelegateType listener);
        virtual void operator-= (DelegateType listener);
      private:
        std::list<DelegateType> listenerList;  // pointer to object
    };
  }
}

#endif
