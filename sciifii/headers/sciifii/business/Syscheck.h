
#ifndef SYSCHECK_H_
#define SYSCHECK_H_

#include "common/Installer.h"
#include <vector>
#include <map>

typedef struct 
{
	bool isStub;
	u16 revision;
} CheckDescriptor;

class Syscheck : public Installer
{
  public:
    Syscheck(const std::string& resultLog);
    virtual bool Prepare();
    virtual void Install();
    void AddStub(u8 tid,u16 revision);
    void SendToLog();

  private :
    std::string fileName;
    std::map<u8, CheckDescriptor> stubList;
    bool CheckESIdentify();
    bool CheckFlashAccess();
    bool CheckNANDAccess();
    bool CheckBoot2Access();
    bool CheckUSB2(u32 titleID);
    bool IsIosStub(u8 tid,u16 revision);
    bool CheckFakeSignature();
		u32 GetDeviceID();
		u32 GetBoot2Version();
		bool CheckBootmiiIOS(u8 id, const CheckDescriptor& descriptor);
		void DeleteFakeTicket();
		u32 GetSysMenuVersion();
};


#endif /* SYSCHECK_H_ */
