#include "Preloader.h"

#include <libutils/fs/File.h>
#include <libutils/exception/Exception.h>
#include <malloc.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include "../../build/priiloader_dat.h"

using namespace std;

Preloader::Preloader()
: bootCid(0)
{}

bool Preloader::Prepare()
{
	return true;
}

void Preloader::Install()
{
	OnProgress("Getting sysMenu ticket.", 0.1);
	if(!File::Exists("wii:/ticket/00000001/00000002.tik"))
		throw Exception("System menu ticket not found!", -1);
		
	//Getting boot index
	static u32 tmd_size ATTRIBUTE_ALIGN(32);
	static u64 title_id ATTRIBUTE_ALIGN(32)=0x0000000100000002LL;
	
	OnProgress("Getting sysMenu tmd.", 0.2);
	s32 ret = ES_GetStoredTMDSize(title_id,&tmd_size);
	if(ret < 0)
		throw Exception("Unable to find System Menu TMD size.", ret);
		
	signed_blob *s_tmd = (signed_blob*)memalign(32,(tmd_size+32)&(~31));
	if(!s_tmd)
		throw Exception("Not enough memory!", -1);
		
	memset(s_tmd, 0, (tmd_size+32)&(~31));
	ret = ES_GetStoredTMD(title_id, s_tmd, tmd_size);
	if(ret < 0)
		throw Exception("Cant read SysMenu tmd!", -1);
		
	tmd* tmd_data = (tmd*)SIGNATURE_PAYLOAD(s_tmd);
	
	OnProgress("Getting sysMenu boot index.", 0.3);
	for(u32 contentIndex = 0; contentIndex < tmd_data->num_contents; ++contentIndex)
	{
		if (tmd_data->contents[contentIndex].index == tmd_data->boot_index)
		{
			bootCid = tmd_data->contents[contentIndex].cid;
			break;
		}
	}
	if(bootCid == 0)
		throw Exception("Boot index not found!", -1);
		
	free(s_tmd);
	
	OnProgress("Copiing sysMenu ticket.", 0.4);
	//copy of the ticket
	if(!File::Exists("wii:/title/00000001/00000002/content/ticket"))
	{
		Buffer ticket = File::ReadToEnd("wii:/ticket/00000001/00000002.tik");
		File &f_tik = File::Create("wii:/title/00000001/00000002/content/ticket");
		try
		{
			f_tik.Write(ticket);
			f_tik.Close();
			delete &f_tik;
		}
		catch(...)
		{
			f_tik.Close();
			delete &f_tik;
			throw Exception("Error copying ticket!", -1);
		}
	}
	
	OnProgress("Copiing sysMenu.", 0.5);
	//copy of the systemMenu		
	stringstream outFile;
	outFile << "wii:/title/00000001/00000002/content/1" << setw(7) << setfill('0') << hex << bootCid << ".app";
	
	//If the backup is already done, we quit.
	if(!File::Exists(outFile.str()))
	{
		stringstream inFile;
		inFile << "wii:/title/00000001/00000002/content/" << setw(8) << setfill('0') << hex << bootCid << ".app";
		
		Buffer sysMenu = File::ReadToEnd(inFile.str());
		File &f_sys = File::Create(outFile.str());
		try
		{
			f_sys.Write(sysMenu);
			f_sys.Close();
			delete &f_sys;
		}
		catch(...)
		{
			f_sys.Close();
			delete &f_sys;
			throw Exception("Error copying SysMenu!", -1);
		}
	}
	
	stringstream sysMenuApp;
	sysMenuApp << "wii:/title/00000001/00000002/content/" << setw(8) << setfill('0') << hex << bootCid << ".app";
	
	stringstream backup;
	backup << "wii:/title/00000001/00000002/content/1" << setw(7) << setfill('0') << hex << bootCid << ".app";
	
	try
	{
		OnProgress("Deleting old preloader datas.", 0.6);
		File::Delete("wii:/title/00000001/00000002/data/loader.ini");
		
		OnProgress("Deleting sysMenu.", 0.7);
		Buffer originalPloader(priiloader_dat, priiloader_dat_size);
		File::Delete(sysMenuApp.str());
	
		OnProgress("Creating priiloader.", 0.8);
		File &ploader = File::Create(sysMenuApp.str());
		ploader.Write(originalPloader);
		ploader.Close();
		delete &ploader;
	
		//checking installation
		OnProgress("Checking Priiloader.", 0.9);
		Buffer copiedPloader = File::ReadToEnd(sysMenuApp.str());
		
		if(copiedPloader.Length() != 0 || copiedPloader.Checksum() != originalPloader.Checksum())
		{
			File::Delete(sysMenuApp.str());
			Buffer b_backup = File::ReadToEnd(backup.str());
			File &f_backup = File::Create(sysMenuApp.str());
			f_backup.Write(b_backup);
			f_backup.Close();
			OnProgress("Installation failed, sysMenu restored.", 1);
			delete &f_backup;
		}
		else
			OnProgress("Priiloader installation done!", 1);
	}
	catch(Exception &ex)
	{
		Buffer b_backup = File::ReadToEnd(backup.str());
		File &ploader = File::Create(sysMenuApp.str());
		ploader.Write(b_backup);
		ploader.Close();
		delete &ploader;
		OnProgress("Error, sysMenu restored.", 1);
		throw;
	}
	catch(...)
	{
		Buffer b_backup = File::ReadToEnd(backup.str());
		File &ploader = File::Create(sysMenuApp.str());
		ploader.Write(b_backup);
		ploader.Close();
		delete &ploader;
		OnProgress("Error, sysMenu restored.", 1);
		throw;
	}
}