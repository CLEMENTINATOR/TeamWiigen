
#ifndef SYSCHECK_H_
#define SYSCHECK_H_

#include "common/Installer.h"
#include <vector>

typedef struct {
	u32 tid;
	u32 rev;
}Stub;
class Syscheck : public Installer
{
  public:
    Syscheck(std::string s);
    virtual ~Syscheck();
    virtual bool Prepare();
    virtual void Install();
    void AddStub(u32 tid,u32 revision);
  private :
    std::string fileName;
    std::vector<Stub> stubList;
    bool CheckESIdentify();
    bool CheckFlashAccess();
    bool CheckNANDAccess();
    bool CheckBoot2Access();
    bool CheckUSB2();
    bool IsIosStub(u32 tid,u32 revision);
    bool CheckFakeSignature();
};


#endif /* SYSCHECK_H_ */
