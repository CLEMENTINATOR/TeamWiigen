#ifndef _EVENTARGS_H_
#define _EVENTARGS_H_

#include "Object.h"
#include <string>

namespace Libwiisys
{
  /**
   * \class EventArgs
   * \brief Events args handled in Event use
   */
  class EventArgs : public Object
  {
    public :
      virtual std::string GetType()
      {
        return "Libwiisys::EventArgs,"+Object::GetType();
      }
  };

}

#endif
