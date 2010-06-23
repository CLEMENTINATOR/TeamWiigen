#ifndef _SYSTEM_SIMPLE_PATCH_H_
#define _SYSTEM_SIMPLE_PATCH_H_

#include <ogcsys.h>
#include <string>
#include "../com/Buffer.h"
#include "../events/TitleEventArgs.h"
#include "Patch.h"
namespace Libwiisys { namespace System { namespace Patching {
class SimplePatch : public Patch
{
private:
	u8* _pattern;
	u8* _patch;
	u32 _length;

protected:
	u32 Patching(TitleEventArgs &processControl) const;

public:

	SimplePatch(const u8* pattern, const u8* patch, const u32 length, const std::string &module = "");
	SimplePatch(const SimplePatch& patch);
	~SimplePatch();
	SimplePatch& operator=(const SimplePatch& patch);

	/* ES Patches */
	static SimplePatch* ES_HashCheck_Old();
	static SimplePatch* ES_HashCheck_New();
	static SimplePatch* ES_Identify();
	static SimplePatch* ES_OpenTitleContent1();
	static SimplePatch* ES_OpenTitleContent2();
	static SimplePatch* ES_ReadContent();
	static SimplePatch* ES_CloseContent();
	static SimplePatch* ES_SetUIDCheck();
	static SimplePatch* ES_TitleVersionCheck();
	static SimplePatch* ES_TitleDeleteCheck();
	static SimplePatch* ES_MEM2Protection();

	/* FFS Patches */
	static SimplePatch* FFS_PermsCheck();

	/* DIP Patches */
	static SimplePatch* DIP_UnencryptedLimit();
	static SimplePatch* DIP_EnableDvdVideo();

	/* Other patches */
	static SimplePatch* KoreanKey_EnablePatch();

	static SimplePatch* getPatch(const std::string &s);


};
}
}
}
#endif
