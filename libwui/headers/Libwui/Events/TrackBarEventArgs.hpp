#ifndef _UI_EVENTS_TRACKBAREVENTARGS_H_
#define _UI_EVENTS_TRACKBAREVENTARGS_H_

#include <Libwiisys/EventArgs.h>
#include <gctypes.h>

namespace Libwui
{
  namespace Events
  {
    class TrackBarEventArgs : public Libwiisys::EventArgs
    {
      private:
        u32 _value;
      public:
        TrackBarEventArgs(u32 val);
        u32 Value();
    };
  }
}
#endif
