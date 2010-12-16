#ifndef _UI_EVENTS_TRACKBAREVENT_H_
#define _UI_EVENTS_TRACKBAREVENT_H_

#include <Libwiisys/Object.h>

#include "TrackBarEventArgs.hpp"
#include <list>
#include <FastDelegate.h>

namespace Libwui
{
  namespace Events
  {
    class TrackBarEvent : public Libwiisys::Object
    {
      public:
        typedef fastdelegate::FastDelegate2<Object*,TrackBarEventArgs*> DelegateType;
        virtual void operator()(Object* sender, TrackBarEventArgs* args);
        virtual void operator+= (DelegateType listener);
        virtual void operator-= (DelegateType listener);
      private:
        std::list<DelegateType> listenerList;  // pointer to object
    };
  }
}

#endif
