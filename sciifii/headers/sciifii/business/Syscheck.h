
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
		CheckDescriptor GetIosDescriptor(u8 iosId);
		bool IsIosStub(u8 iosId, u16 revision);
		u32 GetDeviceId();
		u32 GetBoot2Version();
		bool HasFakeSignature();
		bool HasESIdentify();
		bool HasFlashAccess();
		bool HasNANDAccess();
		bool HasBoot2Access();
		bool HasUSB2();
};


#endif /* SYSCHECK_H_ */
