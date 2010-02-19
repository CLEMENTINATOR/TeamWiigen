#ifndef _SYSTEM_PLUGIN_PATCH_H_
#define _SYSTEM_PLUGIN_PATCH_H_

#include <ogcsys.h>
#include <string>
#include <vector>
#include "../com/Buffer.h"
#include "../events/TitleEventArgs.h"
#include "Patch.h"
#include "SimplePatch.h"

/* ARM binary header structure */
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
	std::vector<SimplePatch*> _commandHandles;

	bool IsElf(u8* buffer) const;
	u32 FindIOSVersionIndex(const Buffer& b) const;
	u32 FindPlugedSegment(u8* elf, u32 moduleToSkip) const;
	u32 FindBssSegment(u8* elf, u32 moduleToSkip) const;
	u32 FindSegmentSize(u8* elf, u32 segmentIndex) const;
	u64 GetElfSize(const u8* elf) const;
	void Plug(u32 segmentIndex, u32 bssSegmentIndex, u8* source, u8* dest) const;
	
protected:
	u32 Patching(TitleEventArgs &processControl) const;
	
public:
	
	PluginPatch(const Buffer& plugin, const u32 offset, const u32 bssNewSize, const std::string &module);
	PluginPatch(const PluginPatch& patch);
	~PluginPatch();
	PluginPatch& operator=(const PluginPatch& patch);
	void DefineCommandHandle(SimplePatch* handle);
};

#endif
