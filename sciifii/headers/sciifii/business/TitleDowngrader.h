#ifndef _IOSDOWNGRADER_H_
#define _IOSDOWNGRADER_H_

#include <Libwiisys/Object.h>
#include "common/Installer.h"

class TitleDowngrader : public Installer
{
  private:
    u64 _id;
    u16 _neededRevision;

    void DowngradeTmd(Libwiisys::Object* sender, Libwiisys::System::Event::TitleEventArgs *args);
    void SkipStep(Libwiisys::Object* sender, Libwiisys::System::Event::TitleEventArgs *args);

  public:
    TitleDowngrader(u64 titleId, u16 neededRevision);
    bool Prepare();
    void Install();
    void SendToLog();
};

#endif
