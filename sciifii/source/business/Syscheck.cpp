#include <sciifii/business/common/FileManager.h>
#include <sciifii/business/Syscheck.h>
#include <sciifii/Config.h>
#include <libwiisys/system/Title.h>
#include <libwiisys/system/Security/Identification.h>
#include <libwiisys/system/Security/Certificate.h>
#include <libwiisys/IO/File.h>
#include <libwiisys/String/UtilString.h>
#include <libwiisys/Buffer.h>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <algorithm>
#include <Libwiisys/logging/Log.h>
#include <Libwiisys/Exceptions/Exception.h>
#include <Libwiisys/fake_su_ticket_dat.h>

using namespace Libwiisys::Logging;
using namespace Libwiisys::Exceptions;
using namespace Libwiisys::System;
using namespace Libwiisys;
using namespace Libwiisys::IO;
using namespace Libwiisys::String;
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
  vector<u8> titleList = Title::GetInstalledIos();
	map<u8, CheckDescriptor> descriptorList;
	u32 stubCount = 0;
  u32 currentIos = Title::GetRunningIOS();
	
  stringstream temp;
	
	//creating report file
	if(File::Exists(fileName))
    File::Delete(fileName);
  File* f = &File::Create(fileName);
	try
	{
		//printing report header
		f->Write("Region: ");
		switch(Config::GetRegion())
		{
			case CONF_REGION_US:
				f->Write("NTSC-U");
				break;

			case CONF_REGION_EU:
				f->Write("PAL");
				break;

			case CONF_REGION_JP:
				f->Write("NTSC-J");
				break;

			case CONF_REGION_KR:
				f->Write("KOR");
				break;

			default:
				f->Write("unknown");
				break;
		}
		temp << endl << "The system menu v" << GetSysMenuVersion() << " is running under IOS" <<  currentIos << " (rev " << Title::GetInstalledTitleVersion(IOS_FULL_ID(currentIos))  << ")" << endl;
		temp << "Hollywood v0x" << hex << *(u32 *)0x80003138 << dec << endl;
		temp << "Console ID: " << GetDeviceID() << endl;
		temp << "Boot2 v" << GetBoot2Version() << endl;
		temp << "Found " << titleList.size() << " titles" << endl;
		f->Write(temp.str());
		temp.str("");
		
		//sorting the list
		sort(titleList.begin(), titleList.end());
		
		//analising titles
		for(vector<u8>::iterator t = titleList.begin(); t != titleList.end(); t++)
		{
			CheckDescriptor desc;
			if(*t == currentIos)
				desc.revision = IOS_GetRevision();
			else
				desc.revision = Title::GetInstalledTitleVersion(IOS_FULL_ID(*t));
			desc.isStub = IsIosStub(*t, desc.revision);
			descriptorList[*t] = desc;
		}
		
		//stub summary
		if ((titleList.size() - stubCount) == 0)
				f->Write("No IOS on this console\n");
		else
		{
			temp << "Found " << titleList.size() - stubCount << "  IOS on this console" << endl;
			f->Write(temp.str());
			temp.str("");
		}

		if (stubCount == 0)
			f->Write("No IOS Stub on this console\n");
		else
		{
			temp << "Found " << stubCount << "IOS Stubs on this console" << endl;
			f->Write(temp.str());
			temp.str("");
		}
		
		
		//genrating the report
		f->Write("\nIOS (revision),IOS Stub,Trucha Bug,ES Identify,Flash Access,NAND Access,Boot2 Access,USB 2.0\n");
		
		f32 step = 0;
		for(vector<u8>::iterator t = titleList.begin(); t != titleList.end(); t++)
		{
			CheckDescriptor desc = descriptorList[*t];
			step++;

			stringstream prog;
			prog<<"Analysing IOS " << *t;
			OnProgress(prog.str(),(f32)((f32)step/(f32)titleList.size()));
			
			temp << "IOS" << *t << " (rev " << desc.revision << "),";
			f->Write(temp.str());
			temp.str("");
			
			if(CheckBootmiiIOS(*t, desc))
			{
				f->Write("No,?,?,?,?,?,?\n");
				continue;
			}
			if (desc.isStub)
			{
				f->Write("Yes,?,?,?,?,?,?\n");
				continue;
			}
			
			f->Close();
			delete f;
			f = NULL;
			Title::ReloadIOS(*t);
			
			f = &File::Open(fileName, FileMode_Write);
			f->Write("No,");
			CheckFakeSignature() ? f->Write("Enabled,") : f->Write("Disabled,");
			CheckESIdentify() ? f->Write("Enabled,") : f->Write("Disabled,");
			CheckFlashAccess() ? f->Write("Enabled,") : f->Write("Disabled,");
			CheckNANDAccess() ? f->Write("Enabled,") : f->Write("Disabled,");
			CheckBoot2Access() ? f->Write("Enabled,") : f->Write("Disabled,");
			CheckUSB2() ? f->Write("Enabled") : f->Write("Disabled");
		}
		
		f->Close();
		delete f;
		f = NULL;
		
		Title::ReloadIOS(currentIos);
		
		OnProgress("Syscheck done !",1);
	}
	catch(Exception &ex)
	{
		if(f)
		{
			f->Close();
			delete f;
		}
		throw;
	}
	catch(...)
	{
		if(f)
		{
			f->Close();
			delete f;
		}
		throw;
	}
}

// Get the system menu version from TMD
u32 Syscheck::GetSysMenuVersion()
{
	u64 TitleID ATTRIBUTE_ALIGN(32) = 0x0000000100000002LL;
	u32 tmdSize ATTRIBUTE_ALIGN(32);

	// Get the stored TMD size for the system menu
	if (ES_GetStoredTMDSize(TitleID, &tmdSize) < 0)
		return 0;

	signed_blob *TMD = (signed_blob *)memalign(32, (tmdSize+32)&(~31));
	memset(TMD, 0, tmdSize);

	// Get the stored TMD for the system menu
	if (ES_GetStoredTMD(TitleID, TMD, tmdSize) < 0)
	{
		free(TMD);
		return false;
	}
	
	// Get the system menu version from TMD
	tmd *rTMD = (tmd *)(TMD+(0x140/sizeof(tmd *)));
	u32 version = rTMD->title_version;

	free(TMD);

	// Return the system menu version
	return version;
}

bool Syscheck::CheckBootmiiIOS(u8 id, const CheckDescriptor& descriptor)
{
  return (id == 254 && descriptor.revision == 31338);
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

void Syscheck:: AddStub(u8 tid,u16 revision)
{
  CheckDescriptor s;
  s.isStub = true;
  s.revision = revision;
  stubList[tid] = s;
}

bool Syscheck::IsIosStub(u8 tid,u16 revision)
{
	if(stubList.find(tid) != stubList.end() && stubList[tid].revision == revision)
		return true;
		
	//manual check
	u32 tmdSize;
	
	// Get the stored TMD size for the title
	if (ES_GetStoredTMDSize(IOS_FULL_ID(tid), &tmdSize) < 0)
		return false;

	signed_blob *b_tmd = (signed_blob *)memalign(32, (tmdSize + 32) & (~31));
	memset(b_tmd, 0, tmdSize);

	// Get the stored TMD for the title
	if (ES_GetStoredTMD(IOS_FULL_ID(tid), b_tmd, tmdSize) < 0)
		return false;
	
	tmd *iosTMD ATTRIBUTE_ALIGN(32);
	iosTMD = (tmd *)SIGNATURE_PAYLOAD(b_tmd);

	// If the version is 00, it's probably a stub
	//
	// Stubs have these things in common:
	//	- Title version is mostly 65280, or even better, the last 2 hexadecimal digits are 0;
	// 	- Stub have one app of their own (type 0x1) and 2 shared apps (type 0x8001).
	bool isStub = false;	
	if (iosTMD->title_version == 0)
		isStub = ((iosTMD->num_contents == 3) && (iosTMD->contents[0].type == 1 && iosTMD->contents[1].type == 0x8001 && iosTMD->contents[2].type == 0x8001));
	else		
		isStub = false;
		
	free(b_tmd);
		
  return isStub;
}

void Syscheck::DeleteFakeTicket()
{
	u64 titleId = 0x100000000LL;
	u32 views;

	// Get number of ticket views
	if(ES_GetNumTicketViews(titleId, &views) >= 0)
		return;

	if (views == 0 || views > 16) 
		return;
	
	// Get ticket views
	tikview *viewdata  = (tikview*)memalign(32, sizeof(tikview) * views);
	if(ES_GetTicketViews(titleId, viewdata, views) >= 0)
	{
		// Remove tickets
		for (u32 cnt = 0; cnt < views; cnt++)
			if(ES_DeleteTicket(&viewdata[cnt]) < 0)
				break;
	}

	free(viewdata);
}

bool Syscheck::CheckFakeSignature()
{
  int ret = ES_AddTicket((signed_blob*) fake_su_ticket_dat, fake_su_ticket_dat_size, (signed_blob*) Certificate::GetContent(), Certificate::GetLength(), 0, 0);
	//removing installed ticket
	if (ret > -1)
		DeleteFakeTicket();
		
	if (ret > -1 || ret == -1028)
		return true;

	return false;
}

void Syscheck::SendToLog()
{
  stringstream txt;
  txt << "Syscheck()";
  Log::WriteLog(Log_Info,txt.str());
}

u32 Syscheck::GetDeviceID()
{
	u32 deviceId = 0;

	if (ES_GetDeviceID(&deviceId) < 0)
		deviceId = 0;
	
	return deviceId;
}

u32 Syscheck::GetBoot2Version()
{
	u32 boot2version = 0;

	if (ES_GetBoot2Version(&boot2version) < 0)
		boot2version = 0;
	
	return boot2version;
}