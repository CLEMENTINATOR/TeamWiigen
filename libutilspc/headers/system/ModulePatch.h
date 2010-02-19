#ifndef _SYSTEM_MODULE_PATCH_H_
#define _SYSTEM_MODULE_PATCH_H_

#include <ogcsys.h>
#include <string>
#include "../com/Buffer.h"
#include "../events/TitleEventArgs.h"
#include "Patch.h"

class ModulePatch : public Patch
{
private:
	u8* _patch;
	u32 _length;
	
protected:
	u32 Patching(TitleEventArgs &processControl) const;
	
public:
	
	ModulePatch(const u8* patch, const u32 length, const std::string &module = "");
	ModulePatch(const ModulePatch& patch);
	~ModulePatch();
	ModulePatch& operator=(const ModulePatch& patch);
};

#endif
