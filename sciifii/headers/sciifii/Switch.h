#ifndef _SWITCH_H_
#define _SWITCH_H_

#include <string>
#include <libwiisys.h>

class Switch : public Libwiisys::Object
{
public:
	std::string Name;
	bool Activated;
	
	Switch(std::string name = "", bool active = false);
};

#endif