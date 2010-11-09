
#include <sciifii/business/Syscheck.h>
#include <libwiisys/system/Title.h>
#include <libwiisys/system/Security/Identification.h>
#include <libwiisys/IO/File.h>
#include <libwiisys/String/UtilString.h>
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace Libwiisys::System;
using namespace Libwiisys::IO;
using namespace Libwiisys::String;
using namespace Libwiisys::System::Security;
using namespace std;

Syscheck::Syscheck(std::string s)
{
  fileName=s;
}

Syscheck::~Syscheck()
{}


bool Syscheck::Prepare()
{
  return true;
}

void Syscheck::Install()
{
  vector<u8> titleList=Title::GetInstalledIos();
  if(File::Exists(fileName))
    File::Delete(fileName);
  File & f = File::Create(fileName);
  int currentIos=Title::GetRunningIOS();
  for(vector<u8>::iterator ite = titleList.begin(); ite != titleList.end(); ite++)
  {

    stringstream s;
    s<<"00000001";
    s<<hex<<setfill('0') << setw(8) << *ite ;
    u64 tid= UtilString::ToU64(s.str().c_str());
    u16 rev=Title::GetInstalledTitleVersion(tid);

    if(IsIosStub(*ite,rev))
    {


    }
    else
    {



      Title::ReloadIOS(*ite);
    }
  }
  f.Close();
  delete &f;
  Title::ReloadIOS(currentIos);
}

bool Syscheck::CheckFlashAccess()
{
  int ret = IOS_Open("/dev/flash", 1);

  if (ret >= 0)
    IOS_Close(ret);

  if (ret < 0)
    return false;
  else
    return true;
}


bool  Syscheck::CheckNANDAccess()
{
  int ret = IOS_Open("/title/00000001/00000002/content/title.tmd", 1);

  if (ret >= 0)
    IOS_Close(ret);

  if (ret < 0)
    return false;
  else
    return true;
}


bool  Syscheck::CheckBoot2Access()
{
  int ret = IOS_Open("/dev/boot2", 1);

  if (ret >= 0)
    IOS_Close(ret);

  if (ret < 0)
    return false;
  else
    return true;
}

bool Syscheck::CheckUSB2()
{
  // Open USB 2.0 module
  int ret = IOS_Open("/dev/usb2", 1);

  // If fail, try old USB 2.0 module
  if (ret < 0)
    ret = IOS_Open("/dev/usb/ehc", 1);

  if (ret >= 0)
    IOS_Close(ret);

  if (ret < 0)
    return false;
  else
    return true;
}

bool  Syscheck::CheckESIdentify()
{
  try
  {
    Identification::IdentifyAs(UserType_SU);
  }
  catch(...)
  {
    return false;
  }
  return true;
}
void Syscheck:: AddStub(u32 tid,u32 revision)
{
  Stub s;
  s.tid=tid;
  s.rev=revision;
  stubList.push_back(s);
}

bool Syscheck::IsIosStub(u32 tid,u32 revision)
{
  for(vector<Stub>::iterator ite = stubList.begin(); ite != stubList.end(); ite++)
  {
    if((*ite).tid ==tid && (*ite).rev==revision)
    {
    	return true;
    }
  }
  return false;
}
