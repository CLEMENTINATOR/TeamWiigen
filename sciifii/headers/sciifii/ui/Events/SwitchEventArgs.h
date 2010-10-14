#ifndef _SWITCH_EVENT_ARGS_H_
#define _SWITCH_EVENT_ARGS_H_

#include <vector>
#include <ogcsys.h>
#include <Libwiisys/EventArgs.h>
#include "../../Switch.h"

class SwitchEventArgs : public Libwiisys::EventArgs
{
  public:
    bool Incremental;
    std::vector<Switch> Switches;
};

#endif
