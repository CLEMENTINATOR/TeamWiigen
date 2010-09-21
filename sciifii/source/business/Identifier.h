#ifndef _IDENTIFIER_H_
#define _IDENTIFIER_H_

#include <string>
#include <libwiisys.h>

#include "common/Installer.h"

class Identifier : public Installer
{
private:
	UserType _type;

public:
	Identifier(UserType type);
	bool Prepare();
	void SendToLog();

	void Install();
};

#endif
