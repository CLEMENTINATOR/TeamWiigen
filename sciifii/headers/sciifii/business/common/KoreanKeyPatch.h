#ifndef _KOREAN_PATCH_H_
#define _KOREAN_PATCH_H_

#include <ogcsys.h>
#include <libwiisys.h>

class KoreanKeyPatch : public Libwiisys::System::Patching::Patch
{
protected:
	u32 Patching(Libwiisys::System::Event::TitleEventArgs &processControl) const;
};

#endif
