#ifndef PRELOADER_H_
#define PRELOADER_H_

#include "common/Installer.h"
#include <ogcsys.h>
#include <Libwiisys/Buffer.h>

class Preloader : public Installer
{
  private:
    u32 bootCid;
    std::string _file;

    Libwiisys::Buffer GetSysMenuTMD();
    u32 GetBootCid(tmd* t);
    void CopyTicket();
    void CopySysMenu();
    void RestoreSysMenu();
    bool CheckPreloader();
    void SendtoLog();
  public:
    Preloader(const std::string& file);
    bool Prepare();
    void Install();
};

#endif
