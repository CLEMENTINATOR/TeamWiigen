#ifndef _CIOS_H_
#define _CIOS_H_

#include <string>
#include <FastDelegate.h>
#include <vector>
#include <Libwiisys/Shell/elf_abi.h>
#include <Libwiisys/system/Patching/SimplePatch.h>

#include "common/Installer.h"

typedef struct
{
  std::string file;
  s32 position;
}
customModule;

class Cios : public Installer
{
  private:
    std::vector<customModule> _modules;
    std::vector<Libwiisys::System::Patching::Patch*> _patches;
    u32 _iosId;
    u16 _iosRevision;
    u32 _slot;
    s32 _ciosRevision;
	std::string _bannerFile;
    bool _delete;

  public:
    Cios(u32 iosId, u16 iosRevision, u32 slot, s32 ciosRevision, std::string bannerFile = "", bool del = false);
    bool Prepare();
    void Install();
    void SendToLog();
    void AddModule(customModule descriptor);
    void AddPatch(Libwiisys::System::Patching::Patch* descriptor);

    virtual ~Cios();
};
#endif
