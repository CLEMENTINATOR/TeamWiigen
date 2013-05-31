#ifndef _SYSTEM_STEP_H_
#define _SYSTEM_STEP_H_

#include "common/Installer.h"

class SystemStep : public Installer
{
  private:
    std::string _action;
    std::string _message;

  public:
    SystemStep(std::string action, std::string message);   
    bool Prepare();
    void Install();
    void SendtoLog();
};

#endif
