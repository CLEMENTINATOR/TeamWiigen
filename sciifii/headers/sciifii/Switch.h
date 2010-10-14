#ifndef _SWITCH_H_
#define _SWITCH_H_

#include <string>
#include <Libwiisys/Object.h>

class Switch : public Libwiisys::Object
{
  public:
    std::string Name;
    std::string Value;
    bool Activated;

    Switch(std::string name = "", bool active = false, std::string value = "");
};

#endif
