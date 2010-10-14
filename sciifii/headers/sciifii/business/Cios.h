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

typedef struct
{
  std::string moduleName;
  std::string file;
  u32 offset;
  u32 bss;
  std::vector<Libwiisys::System::Patching::SimplePatch> handles;
  bool replaceSection;
  u32 segment;
  Elf32_Phdr header;
}
pluginDescriptor;

class Cios : public Installer
{
  private:
    std::vector<customModule> _modules;
    std::vector<pluginDescriptor> _plugins;
    std::vector<Libwiisys::System::Patching::Patch*> _patches;
    u32 _iosId;
    u16 _iosRevision;
    u32 _slot;
    s32 _ciosRevision;
    bool _delete;

  public:
    Cios(u32 iosId, u16 iosRevision, u32 slot, s32 ciosRevision, bool del = false);
    bool Prepare();
    void Install();
    void SendToLog();
    void AddModule(customModule descriptor);
    void AddPlugin(pluginDescriptor descriptor);
    void AddPatch(Libwiisys::System::Patching::Patch* descriptor);

    virtual ~Cios();
};
#endif
