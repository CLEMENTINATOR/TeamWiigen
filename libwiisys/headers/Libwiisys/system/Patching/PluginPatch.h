#ifndef _SYSTEM_PLUGIN_PATCH_H_
#define _SYSTEM_PLUGIN_PATCH_H_

#include <ogcsys.h>
#include <string>
#include <vector>
#include "../../Buffer.h"
#include "../Event/TitleEventArgs.h"
#include "Patch.h"
#include "SimplePatch.h"
#include "../../Shell/elf_abi.h"
namespace Libwiisys { namespace System { namespace Patching {
/**
 * @struct ArmHeader
 * @brief ARM binary header structure
 */
typedef struct {
	u32 headerSize;
	u32 offset;
	u32 size;
	u32 resevered;
} ArmHeader;

class PluginPatch : public Patch
{
private:	
	Buffer _plugin;
	u32 _offset;
	u32 _bssNewSize;
	std::vector<SimplePatch> _commandHandles;
	Elf32_Phdr* _newProgramSection;
	u32 _replaceSection;

	bool IsElf(u8* buffer) const;
	u32 FindIOSVersionIndex(const Buffer& b) const;
	u32 FindPlugedSegment(u8* elf, u32 moduleToSkip) const;
	u32 FindBssSegment(u8* elf, u32 moduleToSkip) const;
	u32 FindSegmentSize(u8* elf, u32 segmentIndex) const;
	u64 GetElfSize(const u8* elf) const;
	void Plug(u32 segmentIndex, u32 bssSegmentIndex, u8* source, u8* dest) const;
	void Plug(u32 segmentIndex, u8* source, u8* dest) const;

protected:
	u32 Patching(Libwiisys::System::Event::TitleEventArgs &processControl) const;

public:

	PluginPatch(const Buffer& plugin, const u32 offset, const u32 bssNewSize, const std::string &module);
	PluginPatch(const Buffer& plugin, Elf32_Phdr newHeader , const std::string &module, u32 replaceSection = 0);
	PluginPatch(const PluginPatch& patch);
	virtual ~PluginPatch();
	PluginPatch& operator=(const PluginPatch& patch);
	void DefineCommandHandle(SimplePatch handle);
};
}
}
}
#endif
