#ifndef PROGRESSEVENTARGS_HPP_
#define PROGRESSEVENTARGS_HPP_

#include <gctypes.h>

namespace Libwiisys
{
  namespace Threading
  {
    class ProgressEventArgs: public EventArgs
    {
      public :
        std::string message;
        f32 percent;
    };
  }
}
#endif /* PROGRESSEVENTARGS_HPP_ */
