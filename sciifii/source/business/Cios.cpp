#include "Cios.h"
#include "../Config.h"

#include <libutils/fs/File.h>
#include <libutils/fs/Path.h>
#include <libutils/system/Title.h>
#include <libutils/system/TitlePatcher.h>
#include <libutils/system/PluginPatch.h>

#include <sstream>
#include <iostream>

#include "../../build/dip_plugin_dat.h"
#include "../../build/es_plugin_dat.h"
#include "../../build/ffs_plugin_dat.h"
#include "../../build/ehci_module_dat.h"
#include "../../build/fat_module_dat.h"
#include "../../build/sdhc_module_dat.h"

using namespace std;

SimplePatch* Cios::DIP_Cmd1()
{
  u8 oldCode[] = { 0xB5, 0xF0, 0x46, 0x57, 0x46, 0x46, 0xB4, 0xC0, 0x68, 0x05, 0x46, 0x8A, 0x21 };
  u8 newCode[] = { 0x4B, 0x00, 0x47, 0x18, 0x20, 0x20, 0x82, 0x01, 0x68, 0x05, 0x46, 0x8A, 0x21 };

  static SimplePatch p(oldCode, newCode, 13, "DIP");
  return &p;
}

SimplePatch* Cios::DIP_Cmd2()
{
  u8 oldCode[] = { 0xB5, 0xF0, 0x46, 0x5F, 0x46, 0x56, 0x46, 0x4D, 0x46, 0x44, 0xB4, 0xF0, 0x4B };
  u8 newCode[] = { 0x4B, 0x00, 0x47, 0x18, 0x20, 0x20, 0x82, 0x05, 0x46, 0x44, 0xB4, 0xF0, 0x4B };

  static SimplePatch p(oldCode, newCode, 13, "DIP");
  return &p;
}

SimplePatch* Cios::FFS_OpenCmd()
{
  u8 oldCode[] = { 0xB5, 0xF0, 0x46, 0x47, 0xB4, 0x80, 0xB0, 0x81, 0x1C, 0x04, 0x1C, 0x05, 0x35 };
  u8 newCode[] = { 0x4B, 0x00, 0x47, 0x18, 0x20, 0x00, 0x72, 0x01, 0x1C, 0x04, 0x1C, 0x05, 0x35 };

  static SimplePatch p(oldCode, newCode, 13, "FFS");
  return &p;
}

SimplePatch* Cios::FFS_CloseCmd()
{
  u8 oldCode[] = { 0xB5, 0x70, 0x26, 0x00, 0x68, 0x84, 0x6A, 0x23, 0x2B, 0x00, 0xD0, 0x00, 0x1C };
  u8 newCode[] = { 0x4B, 0x00, 0x47, 0x18, 0x20, 0x00, 0x72, 0x01, 0x2B, 0x00, 0xD0, 0x00, 0x1C };

  static SimplePatch p(oldCode, newCode, 13, "FFS");
  return &p;
}

SimplePatch* Cios::FFS_ReadCmd()
{
  u8 oldCode[] = { 0xB5, 0xF0, 0x46, 0x57, 0x46, 0x4E, 0x46, 0x45, 0xB4, 0xE0, 0x22, 0x0C, 0x18 };
  u8 newCode[] = { 0x4B, 0x00, 0x47, 0x18, 0x20, 0x00, 0x72, 0x01, 0xB4, 0xE0, 0x22, 0x0C, 0x18 };

  static SimplePatch p(oldCode, newCode, 13, "FFS");
  return &p;
}

SimplePatch* Cios::FFS_WriteCmd()
{
  u8 oldCode[] = { 0xB5, 0xF0, 0x46, 0x57, 0x46, 0x4E, 0x46, 0x45, 0xB4, 0xE0, 0x21, 0x0C, 0x18 };
  u8 newCode[] = { 0x4B, 0x00, 0x47, 0x18, 0x20, 0x00, 0x72, 0x01, 0xB4, 0xE0, 0x21, 0x0C, 0x18 };

  static SimplePatch p(oldCode, newCode, 13, "FFS");
  return &p;
}

SimplePatch* Cios::FFS_SeekCmd()
{
  u8 oldCode[] = { 0xB5, 0x10, 0x1C, 0x04, 0x34, 0x0C, 0x68, 0x81, 0x6A, 0x08, 0x28, 0x00, 0xD1 };
  u8 newCode[] = { 0x4B, 0x00, 0x47, 0x18, 0x20, 0x00, 0x72, 0x01, 0x6A, 0x08, 0x28, 0x00, 0xD1 };

  static SimplePatch p(oldCode, newCode, 13, "FFS");
  return &p;
}

SimplePatch* Cios::FFS_IoctlCmd()
{
  u8 oldCode[] = { 0xB5, 0xF0, 0xB0, 0x9C, 0x24, 0x00, 0x1C, 0x05, 0x35, 0x0C, 0x68, 0x81, 0x26 };
  u8 newCode[] = { 0x4B, 0x00, 0x47, 0x18, 0x20, 0x00, 0x72, 0x01, 0x35, 0x0C, 0x68, 0x81, 0x26 };

  static SimplePatch p(oldCode, newCode, 13, "FFS");
  return &p;
}

SimplePatch* Cios::FFS_IoctlvCmd()
{
  u8 oldCode[] = { 0xB5, 0xF0, 0xB0, 0x81, 0x1C, 0x04, 0x34, 0x0C, 0x68, 0x85, 0x68, 0xC3, 0x2B };
  u8 newCode[] = { 0x4B, 0x00, 0x47, 0x18, 0x20, 0x00, 0x72, 0x01, 0x68, 0x85, 0x68, 0xC3, 0x2B };

  static SimplePatch p(oldCode, newCode, 13, "FFS");
  return &p;
}

SimplePatch* Cios::ES_Cmd()
{
  u8 oldCode[] = { 0xB5, 0x70, 0xB0, 0x88, 0x68, 0x85, 0x1C, 0x01, 0x31, 0x0C, 0x22, 0xC0 };
  u8 newCode[] = { 0x4B, 0x00, 0x47, 0x18, 0x20, 0x10, 0xB2, 0x01, 0x31, 0x0C, 0x22, 0xC0 };

  static SimplePatch p(oldCode, newCode, 12, "ES");
  return &p;
}

bool Cios::Prepare()
{
	u64 source = 0x0000000100000000ULL + 38;

	stringstream wadFile;
	wadFile << Config::WorkingDirectory() << "/" << Title::GetWadFormatedName(source,3867);

	if(!File::Exists(wadFile.str()))
	{
		if(Config::HasNetwork())
		{
			Title ios;

			stringstream downloadMessage;
			downloadMessage << "Downloading IOS " << 38 << " version " << 3867 << " from NUS";
			OnProgress(downloadMessage.str(), 0.25);
			ios.LoadFromNusServer(source, 3867, Config::WorkingDirectory());

			stringstream packMessage;
			packMessage << "Saving as "<< Path::GetFileName(wadFile.str());
			OnProgress(packMessage.str(), 0.7);
			ios.PackAsWad(wadFile.str());
		}
		else
		{
			cout << "You arent connected to the network and some wads are missing." << endl
				 << "Please refer to the readme.";
			return false;
		}
	}

	OnProgress("Waninkoko cIOS preparation done.", 1);

	return true;
}

void Cios::Install()
{
	TitlePatcher cios(0x0000000100000000ULL + 249, 17);

	/* ES Patches */
	cios.AddPatch(SimplePatch::ES_HashCheck_Old());
	cios.AddPatch(SimplePatch::ES_HashCheck_New());
	cios.AddPatch(SimplePatch::ES_Identify());
	cios.AddPatch(SimplePatch::ES_OpenTitleContent1());
	cios.AddPatch(SimplePatch::ES_OpenTitleContent2());
	cios.AddPatch(SimplePatch::ES_ReadContent());
	cios.AddPatch(SimplePatch::ES_CloseContent());
	cios.AddPatch(SimplePatch::ES_SetUIDCheck());
	cios.AddPatch(SimplePatch::ES_TitleVersionCheck());
	cios.AddPatch(SimplePatch::ES_TitleDeleteCheck());
	cios.AddPatch(SimplePatch::ES_MEM2Protection());

	/* FFS Patches */
	cios.AddPatch(SimplePatch::FFS_PermsCheck());

	/* DIP Patches */
	cios.AddPatch(SimplePatch::DIP_UnencryptedLimit());
	cios.AddPatch(SimplePatch::DIP_EnableDvdVideo());

	/* DIP Plugin */
	Buffer dipPlugin(dip_plugin_dat, dip_plugin_dat_size);
	PluginPatch dipPatch(dipPlugin, 0x200, 0x2C000, "DIP");
	dipPatch.DefineCommandHandle(Cios::DIP_Cmd1());
	dipPatch.DefineCommandHandle(Cios::DIP_Cmd2());
	cios.AddPatch(&dipPatch);

	/* ES Plugin */
	Buffer esPlugin(es_plugin_dat, es_plugin_dat_size);
	PluginPatch esPatch(esPlugin, 0x200, 0x5000, "ES");
	esPatch.DefineCommandHandle(Cios::ES_Cmd());
	cios.AddPatch(&esPatch);

	/* FFS Plugin */
	Buffer ffsPlugin(ffs_plugin_dat, ffs_plugin_dat_size);
	PluginPatch ffsPatch(ffsPlugin, 0x7200 , 0x47000, "FFS");
	ffsPatch.DefineCommandHandle(Cios::FFS_OpenCmd());
	ffsPatch.DefineCommandHandle(Cios::FFS_CloseCmd());
	ffsPatch.DefineCommandHandle(Cios::FFS_ReadCmd());
	ffsPatch.DefineCommandHandle(Cios::FFS_WriteCmd());
	ffsPatch.DefineCommandHandle(Cios::FFS_SeekCmd());
	ffsPatch.DefineCommandHandle(Cios::FFS_IoctlCmd());
	ffsPatch.DefineCommandHandle(Cios::FFS_IoctlvCmd());
	cios.AddPatch(&ffsPatch);

	/* ehci module */
	TitleModule ehciModule(ehci_module_dat, ehci_module_dat_size, 3);
	cios.AddModule(&ehciModule);

	/* fat module */
	TitleModule fatModule(fat_module_dat, fat_module_dat_size);
	cios.AddModule(&fatModule);

	/* sdhc module */
	TitleModule sdhcModule(sdhc_module_dat, sdhc_module_dat_size);
	cios.AddModule(&sdhcModule);

	stringstream wadFile;
	wadFile << Config::WorkingDirectory() << "/" << Title::GetWadFormatedName(0x0000000100000000ULL + 38,3867);

	OnProgress("Deleting old IOS249 or stub.", 0.2);
	Title::Uninstall(0x0000000100000000ULL + 249);

	OnProgress("Load base wad for cios and patch it!", 0.4);
	cios.LoadFromWad(wadFile.str(), Config::WorkingDirectory());

	OnProgress("Installation of the cIOS!", 0.8);
	cios.Install();

	OnProgress("cIOS installed.", 1);
}
