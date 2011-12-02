#ifndef _TITLE_STEP_H_
#define _TITLE_STEP_H_

#include "common/Installer.h"
#include <Libwiisys/system/Patching/TitlePatcher.h>

typedef enum
{
  ti_Install,
  ti_Uninstall,
  ti_PackAsWad,
  ti_Extract,
  ti_Decrypt,
  ti_Update,
} TitleAction;

class TitleStep : public Installer
{
  private:
    u64 _id;
    u16 _revision;
    TitleAction _action;
    std::string _file;
	std::string _key;
    std::string _path;
	Libwiisys::System::Patching::Fakesign_Type _fakesign;
	bool _skipUpdate;

  public:
    TitleStep(u64 titleId, u16 revision, TitleAction a, std::string path = "",Libwiisys::System::Patching::Fakesign_Type fakesign = Libwiisys::System::Patching::Fakesign_None);
    TitleStep(std::string key, TitleAction a, std::string path = "",Libwiisys::System::Patching::Fakesign_Type fakesign = Libwiisys::System::Patching::Fakesign_None);
    bool Prepare();
    void Install();
    void SendtoLog();
};

#endif
