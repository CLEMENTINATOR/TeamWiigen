
#include <sciifii/business/Syscheck.h>
#include <libwiisys/system/Title.h>
#include <libwiisys/system/Security/Identification.h>
#include <libwiisys/IO/File.h>
#include <libwiisys/String/UtilString.h>
#include <libwiisys/Buffer.h>
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace Libwiisys::System;
using namespace Libwiisys;
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
  OnProgress("Syscheck preparation done !",1);
  return true;
}

void Syscheck::Install()
{
  vector<u8> titleList=Title::GetInstalledIos();
  int currentIos=Title::GetRunningIOS();
  stringstream report,stubs;
  report<<"IOS,"<<"Revision,"<<"Flash Access,"<<"Nand Access,"<<"Boot2 Access,"<<"Usb2,"<<"Trucha,"<<"ES_Identify,"<<endl;
  stubs<<"Report"<<endl;
  f32 step=0;
  for(vector<u8>::iterator ite = titleList.begin(); ite != titleList.end(); ite++)
  {
    step++;
    u32 titleId = (u32)(*ite) & 0xFFFFFFFF;
    u64 tid=0x0000000100000000ULL | titleId;


    if(titleId==currentIos) // current ios
    	continue;

    u16 rev;
    rev=Title::GetInstalledTitleVersion(tid);

    stringstream prog;
    prog<<"Analysing IOS "<<titleId<<endl;
    OnProgress(prog.str(),(f32)((f32)step/(f32)titleList.size()));


    if(IsIosStub(titleId,rev))
    {
      stubs<<(titleId)<<","<<(rev)<<","<<endl;
    }
    else
    {
      report<<(titleId)<<","<<(rev)<<",";
      Title::ReloadIOS(titleId);

      if(CheckFlashAccess())
        report<<"OK,";
      else
        report<<"NOK,";

      if(CheckNANDAccess())
        report<<"OK,";
      else
        report<<"NOK,";

      if(CheckBoot2Access())
        report<<"OK,";
      else
        report<<"NOK,";

      if(CheckUSB2())
        report<<"OK,";
      else
        report<<"NOK,";

      if(CheckFakeSignature())
        report<<"TODO,";
      else
        report<<"TODO,";

      if(CheckESIdentify())
        report<<"OK,";
      else
        report<<"NOK,";

      report<<endl;
    }
  }
  OnProgress("Writing report",1);
  if(File::Exists(fileName))
    File::Delete(fileName);
  File & f = File::Create(fileName);
  Buffer b;
  b.Append(report.str().c_str(),strlen(report.str().c_str()));
  f.Write(b);
  b.Clear();
  b.Append(stubs.str().c_str(),strlen(stubs.str().c_str()));
  f.Write(b);
  f.Close();
  delete &f;
  Title::ReloadIOS(currentIos);
  OnProgress("Syscheck done !",1);
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

bool Syscheck::CheckFakeSignature()
{
  return true;
}
