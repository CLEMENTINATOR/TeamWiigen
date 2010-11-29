#ifndef _STOP_SCIIFII_STEP_H_
#define _STOP_SCIIFII_STEP_H_

#include "common/Installer.h"

class StopSciifiiStep : public Installer
{
  public:
    bool Prepare();
    void Install();
    void SendToLog();
};

#endif
