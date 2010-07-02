#ifndef _CERTIFICATE_H_
#define _CERTIFICATE_H_

#include "../../Object.h"
#include "../../Buffer.h"
#include <ogcsys.h>

#define CERTIFICATE_LEN	0x280
namespace Libwiisys { namespace System { namespace Security {
/**
 * \class Certificate
 * \brief This class handles the use of Wii Certificate.
 * \author Arasium, Teton, Fanta
 * \version 1.0
 */

class Certificate : public Object
{
public:
	static signed_blob* GetContent();
	static u32 GetLength();

private:
	Buffer content;

	static Certificate& Current();
	Certificate();
};
}
}
}
#endif
