#ifndef _IDENTIFICATION_H_
#define _IDENTIFICATION_H_

#include <gccore.h>
#include "../../Object.h"
#include "UserType.h"

namespace Libwiisys { namespace System { namespace Security {


/**
 * \class Identification
 * \brief This class allow identification to get privileges or rights access
 * \author Arasium, Teton, Fanta
 * \version 1.0
 */
class Identification : public Object
{
public:
	static void IdentifyAs(UserType user);

private:
	static void Identify(const u8 *certs, u32 certs_size, const u8 *idtmd, u32 idtmd_size, const u8 *idticket, u32 idticket_size);
};
}
}
}
#endif
