#ifndef _COMPOSITE_INSTALLER_H_
#define _COMPOSITE_INSTALLER_H_

#include <vector>
#include "common/Installer.h"

class CompositeInstaller : public Installer
{
  private:
    std::vector<Installer*> _steps;
    std::string _name;
    u32 _currentStep;
    bool _cleaned;

    void DisplayProgress(Object* sender, Libwiisys::Threading::ProgressEventArgs* args);

  public:
    CompositeInstaller(const std::string& name);
    void SendToLog();
    void AddStep(Installer* step);
    bool Prepare();
    void Install();
    virtual ~CompositeInstaller();
};

#endif
