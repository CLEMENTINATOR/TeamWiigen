#ifndef _SYSTEM_MODULE_PATCH_H_
#define _SYSTEM_MODULE_PATCH_H_

#include <ogcsys.h>
#include <string>
#include "../../Buffer.h"
#include "../Event/TitleEventArgs.h"
#include "Patch.h"
namespace Libwiisys { namespace System { namespace Patching {

class ModulePatch : public Patch
{
private:
	u8* _patch;
	u32 _length;

protected:
	u32 Patching(System::Event::TitleEventArgs &processControl) const;

public:

	ModulePatch(const u8* patch, const u32 length, const std::string &module = "");
	ModulePatch(const ModulePatch& patch);
	virtual ~ModulePatch();
	ModulePatch& operator=(const ModulePatch& patch);
};
}
}
}
#endif
