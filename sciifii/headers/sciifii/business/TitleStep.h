#ifndef _TITLE_STEP_H_
#define _TITLE_STEP_H_

#include "common/Installer.h"

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
    std::string _path;

  public:
    TitleStep(u64 titleId, u16 revision, TitleAction a, std::string path = "");
    TitleStep(std::string file, TitleAction a, std::string path = "");
    bool Prepare();
    void Install();
    void SendtoLog();
};

#endif
