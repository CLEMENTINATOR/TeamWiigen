#include <sciifii/business/Syscheck.h>
#include <sciifii/Config.h>
#include <Libwiisys/system/Title.h>
#include <Libwiisys/system/Security/Identification.h>
#include <Libwiisys/IO/File.h>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <algorithm>
#include <Libwiisys/logging/Log.h>
#include <Libwiisys/Exceptions/Exception.h>
#include <Libwiisys/fake_su_ticket_dat.h>
#include <Libwiisys/system/Security/Certificate.h>

using namespace Libwiisys::Logging;
using namespace Libwiisys::Exceptions;
using namespace Libwiisys::System;
using namespace Libwiisys;
using namespace Libwiisys::IO;
using namespace Libwiisys::System::Security;
using namespace std;

Syscheck::Syscheck(const string& resultLog)
    : fileName(resultLog)
{}

bool Syscheck::Prepare()
{
  OnProgress("Syscheck preparation done !",1);
  return true;
}

void Syscheck::Install()
{
  u32 runningIOS = Title::GetRunningIOS();
  u32 nbStub = 0;

  vector<u8> iosList = Title::GetInstalledIos();
  if(iosList.size() == 0)
    throw Exception("Syscheck : No ios found!");

  map<u8, CheckDescriptor> descriptors;

  sort(iosList.begin(), iosList.end());
  for(vector<u8>::iterator ios = iosList.begin(); ios != iosList.end(); ios++)
  {
    descriptors[*ios] = GetIosDescriptor(*ios);
    if(descriptors[*ios].isStub)
      nbStub ++;
  }

  ostringstream report;
  report << "Syscheck is running under IOS" << runningIOS << "(rev " << Title::GetInstalledTitleVersion(IOS_FULL_ID(runningIOS)) << ")." << endl << endl;
  report << "Console ID: " << GetDeviceId() << "." << endl;

  report << "Region: ";

  switch (Config::GetRegion())
  {
    case CONF_REGION_US:
      report << ": NTSC-U.";
      break;

    case CONF_REGION_EU:
      report << ": PAL.";
      break;

    case CONF_REGION_JP:
      report << ": NTSC-J.";
      break;

    case CONF_REGION_KR:
      report << ": KOR.";
      break;
  }

  report << endl << "Hollywood v0x" << hex << SYS_GetHollywoodRevision() << dec << "." << endl;
  report << "Boot2 v" << GetBoot2Version() << "." << endl;
  report << "System Menu v" << Title::GetInstalledTitleVersion(IOS_FULL_ID(2)) << endl << endl << endl;
  report << "Found " << iosList.size() << " titles." << endl;

  if(iosList.size() == nbStub || nbStub == 0)
  {
    if (iosList.size() == nbStub)
      report << "No IOS on this console!" << endl;
    else
      report << "Found " << iosList.size() - nbStub << " IOS on this console." << endl;

    if (nbStub == 0)
      report << "No IOS Stub on this console!" << endl;
    else
      report << "Found " << nbStub << " IOS Stubs on this console." << endl;
  }
  else
    report << "Found " << iosList.size() - nbStub << " IOS and " << nbStub << " IOS Stubs on this console." << endl;

  //csv header
  report << "IOS (revision),IOS Stub,Trucha Bug,ES_Identify,Flash Access,NAND Access,Boot2 Access,USB 2.0" << endl;

  u32 nb=1;
  for(map<u8, CheckDescriptor>::iterator desc = descriptors.begin(); desc != descriptors.end(); desc++)
  {
    report << "IOS" << (u32)desc->first << " (rev " << desc->second.revision << ")";
    {
      stringstream s;
      s<<"Analysing  IOS" << (u32)desc->first << " (rev " << desc->second.revision << ")";
      OnProgress(s.str(),(f32)nb/(f32)descriptors.size());
      nb++;
    }
    if (desc->first == 254)
      report << "No,?,?,?,?,?,?";
    else if(desc->second.isStub)
      report << "Yes,?,?,?,?,?,?";
    else
    {
      usleep(40000);
      Title::ReloadIOS(desc->first);
      report << "No,";

      report << (HasFakeSignature() ? "Enabled" : "Disabled") << ",";
      report << (HasESIdentify()    ? "Enabled" : "Disabled") << ",";
      report << (HasFlashAccess()   ? "Enabled" : "Disabled") << ",";
      report << (HasNANDAccess()    ? "Enabled" : "Disabled") << ",";
      report << (HasBoot2Access()   ? "Enabled" : "Disabled") << ",";
      report << (HasUSB2()          ? "Enabled" : "Disabled");
    }

    report << endl;

  }
  usleep(40000);
  Title::ReloadIOS(runningIOS);

  // Get and display the current date
  time_t    rawtime;

  time(&rawtime);
  struct tm today = *localtime(&rawtime);
  report << endl << "Report generated on " << today.tm_year + 1900 << "-" << today.tm_mon + 1 << "-" << today.tm_mday << "." << endl;

  if(File::Exists(fileName))
    File::Delete(fileName);

  File& f = File::Create(fileName);
  f.Write(report.str());
  f.Close();
  delete &f;
  OnProgress("Syscheck done !",1);
}

void Syscheck::AddStub(u8 tid,u16 revision)
{
  CheckDescriptor s;
  s.isStub = true;
  s.revision = revision;
  stubList[tid] = s;
}

CheckDescriptor Syscheck::GetIosDescriptor(u8 iosId)
{
  CheckDescriptor iosDescriptor;
  iosDescriptor.revision = Title::GetInstalledTitleVersion(IOS_FULL_ID(iosId));
  iosDescriptor.isStub = IsIosStub(iosId, iosDescriptor.revision);
  return iosDescriptor;
}

bool Syscheck::IsIosStub(u8 iosId, u16 revision)
{
  //if known ios, we skip the checks
  if(stubList.find(iosId) != stubList.end() && stubList[iosId].revision == revision)
    return true;

  signed_blob* tmdBuffer = Title::GetTitleSignedTmd(IOS_FULL_ID(iosId));
  tmd *iosTMD ATTRIBUTE_ALIGN(32) = (tmd *) SIGNATURE_PAYLOAD(tmdBuffer);

  bool isStub = true;
  // If the version is 00, it's probably a stub
  //
  // Stubs have these things in common:
  // - Title version is mostly 65280, or even better, the last 2 hexadecimal digits are 0;
  //  - Stub have one app of their own (type 0x1) and 2 shared apps (type 0x8001).
  if (((u8)revision) == 0)
    isStub = ((iosTMD->num_contents == 3) && (iosTMD->contents[0].type == 1 && iosTMD->contents[1].type == 0x8001 && iosTMD->contents[2].type == 0x8001));
  else
    isStub = false;

  free(tmdBuffer);

  return isStub;
}

void Syscheck::SendToLog()
{
  stringstream txt;
  txt << "Syscheck()";
  Log::WriteLog(Log_Info,txt.str());
}

u32 Syscheck::GetDeviceId()
{
  u32 deviceId;
  if (ES_GetDeviceID(&deviceId) < 0)
    return 0;

  return deviceId;
}

u32 Syscheck::GetBoot2Version()
{
  u32 boot2version;

  if (ES_GetBoot2Version(&boot2version) < 0)
    boot2version = 0;

  return boot2version;
}
void Syscheck::RemoveTestTicket()
{
  tikview *viewdata = NULL;
  u64  titleId = 0x100000000LL;
  u32  cnt, views;
  s32  ret;

  // Get number of ticket views
  ret = ES_GetNumTicketViews(titleId, &views);

  if (ret < 0)
    return ;

  if (!views)
    return ;
  else
  {
    if (views > 16)
      return ;
  }

  // Get ticket views
  viewdata = (tikview*)memalign(32, sizeof(tikview) * views);
  ret = ES_GetTicketViews(titleId, viewdata, views);

  if (ret < 0)
  {
    free(viewdata);
    return ;
  }
  // Remove tickets
  for (cnt = 0; cnt < views; cnt++)
  {
    ret = ES_DeleteTicket(&viewdata[cnt]);

    if (ret < 0)
	{
	  free(viewdata);
      return ;
	}
  }
  free(viewdata);
  return ;


}
bool Syscheck::HasFakeSignature()
{
  int ret = ES_AddTicket((signed_blob*) fake_su_ticket_dat, fake_su_ticket_dat_size, Certificate::GetContent(), Certificate::GetLength(), 0, 0);

  if (ret > -1)
    RemoveTestTicket();

  if (ret > -1 || ret == -1028)
    return true;

  return false;
}

bool Syscheck::HasESIdentify()
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

bool Syscheck::HasFlashAccess()
{
  int ret = IOS_Open("/dev/flash", 1);

  IOS_Close(ret);

  return (ret >= 0);
}

bool Syscheck::HasNANDAccess()
{
  int ret = IOS_Open("/title/00000001/00000002/content/title.tmd", 1);

  IOS_Close(ret);

  return (ret >= 0);
}

bool Syscheck::HasBoot2Access()
{
  int ret = IOS_Open("/dev/boot2", 1);

  IOS_Close(ret);

  return (ret >= 0);
}

bool Syscheck::HasUSB2()
{
  // Nintendo's IOS58 and Hermes' IOS supports USB 2.0 module
  switch (Title::GetRunningIOS())
  {
    case 58:
      return true;
      break;

    case 202:
      return true;
      break;

    case 222:
      return true;
      break;

    case 223:
      return true;
      break;

    case 224:
      return true;
      break;
  }

  // Open USB 2.0 module
  int ret = IOS_Open("/dev/usb2", 1);

  // If fail, try old USB 2.0 module (EHCI)
  if (ret < 0)
    ret = IOS_Open("/dev/usb/ehc", 1);

  // If fail, try USB 2.0 module from cIOS Hermes v5.1
  if (ret < 0)
    ret = IOS_Open("/dev/usb123", 1);

  IOS_Close(ret);

  return (ret >= 0);
}
