#ifndef _TITLE_STEP_H_
#define _TITLE_STEP_H_

#include "common/Installer.h"
typedef enum
{
  ti_Install,
  ti_Uninstall,
  ti_PackAsWad
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
    TitleStep(u64 titleId, u16 revision,TitleAction a);
    TitleStep(std::string file,std::string path,TitleAction a);
    bool Prepare();
    void Install();
  };

#endif
