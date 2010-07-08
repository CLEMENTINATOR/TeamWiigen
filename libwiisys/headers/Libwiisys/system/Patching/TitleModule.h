#ifndef _TITLE_MODULE_H_
#define _TITLE_MODULE_H_

#include "../../Buffer.h"
namespace Libwiisys { namespace System { namespace Patching {

/**
 * \class TitleModule
 * \brief Class used to patch title modules
 * \author Arasium,Teton,Fanta
 * \version 1.0
 */
class TitleModule : public Buffer
{
private:
	s32 _position;

public:
	TitleModule(const Buffer& buffer, const s32 requiredPosition = -1);
	TitleModule(const u8* buffer, const u64 length, const s32 requiredPosition = -1);
	TitleModule(const TitleModule& module);
	bool IsPositionRequired() const;
	u32 Position() const;
};
}
}
}
#endif
