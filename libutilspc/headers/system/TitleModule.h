#ifndef _TITLE_MODULE_H_
#define _TITLE_MODULE_H_

#include "../com/Buffer.h"

class TitleModule : public Buffer
{
private:
	s32 _position;
	
public:
	TitleModule(const u8* buffer, const u64 length, const s32 requiredPosition = -1);
	bool IsPositionRequired() const;
	u32 Position() const;
};

#endif
