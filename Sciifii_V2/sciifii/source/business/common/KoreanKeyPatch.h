#ifndef _KOREAN_PATCH_H_
#define _KOREAN_PATCH_H_

#include <ogcsys.h>
#include <libutils/events/TitleEventArgs.h>
#include <libutils/system/Patch.h>

class KoreanKeyPatch : public Patch
{
protected:
	u32 Patching(TitleEventArgs &processControl) const;
};

#endif