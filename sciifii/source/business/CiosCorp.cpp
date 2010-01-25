#include "CiosCorp.h"

#include "../Config.h"
#include "common/KoreanKeyPatch.h"

#include <iostream>
#include <sstream>

#include <libutils/com/NetworkRequest.h>
#include <libutils/exception/Exception.h>
#include <libutils/system/TitlePatcher.h>
#include <libutils/system/SimplePatch.h>
#include <libutils/system/ModulePatch.h>
#include <libutils/fs/File.h>

#include "../../build/dip13_dat.h"
#include "../../build/dip17_dat.h"
#include "../../build/es17_dat.h"

using namespace std;

CiosCorp::CiosCorp(const std::string& workingDirectory)
: Installer(workingDirectory)
{}

bool CiosCorp::Prepare()
{
	f32 step = 0;

	for(u32 ciosIndex = 0; ciosIndex < NB_INSTALL_CIOS; ciosIndex++)
	{
		ciosDesc c = installCioses[ciosIndex];
		u64 source = 0x0000000100000000ULL + c.sourceId;

		stringstream wadFile;
		wadFile << wadFolder << "/IOS" << c.sourceId << "v" << c.revision << ".wad";

		if(!File::Exists(wadFile.str()))
		{
			if(c.wadSource != "")
			{
				if(allowIllegal)
				{
					NetworkRequest req(c.wadSource);
					Buffer response = req.GetResponse();

					File &wad = File::Create(wadFile.str());
					wad.Write(response);
					wad.Close();
					delete &wad;
				}
				continue;
			}
			
			if(hasNetwork)
			{
				Title ios;

				stringstream downloadMessage;
				downloadMessage << "Downloading IOS" << c.sourceId << " version " << c.revision << " from NUS";
				cout << downloadMessage.str() << endl;
				//OnProgress(downloadMessage.str(), step/NB_INSTALL_CIOS);
				ios.LoadFromNusServer(source, c.revision, wadFolder);

				stringstream packMessage;
				packMessage << "Saving as IOS" << c.sourceId << "v" << c.revision << ".wad";
				cout << packMessage.str() << endl;
				//OnProgress(downloadMessage.str(), (step + 0.5)/NB_INSTALL_CIOS);
				ios.PackAsWad(wadFile.str());
			}
			else
			{
				cout << "You arent connected to the network and some wads are missing." << endl
				     << "Please refer to the readme.";
				return false;
			}
		}

		//OnProgress("", step/NB_INSTALL_CIOS);
		step += 1;
	}

	return true;
}

void CiosCorp::Install()
{
	ModulePatch dip13(dip13_dat, dip13_dat_size, "DIP");
	dip13.ForbiddenModule = "IOSP";

	ModulePatch dip17(dip17_dat, dip17_dat_size, "DIP");
	dip17.ForbiddenModule = "IOSP";

	ModulePatch es17(es17_dat, es17_dat_size, "ES");

	KoreanKeyPatch kkpatch;

	f32 step = 0;

	for(u32 ciosIndex = 0; ciosIndex < NB_INSTALL_CIOS; ciosIndex++)
	{
		ciosDesc c = installCioses[ciosIndex];
		u64 dest = 0x0000000100000000ULL + c.destId;

		TitlePatcher ciosPatcher(dest, 0xFFFF);

		ciosPatcher.AddPatch(SimplePatch::ES_HashCheck_Old());
		ciosPatcher.AddPatch(SimplePatch::ES_HashCheck_New());

		switch(c.dipVersion)
		{
			case 13:
				ciosPatcher.AddPatch(&dip13);
				break;
			case 17:
				ciosPatcher.AddPatch(&dip17);
				break;
		}

		switch(c.esVersion)
		{
			case 17:
				ciosPatcher.AddPatch(&es17);
				break;
		}

		if(c.IdentifyPatch)
			ciosPatcher.AddPatch(SimplePatch::ES_Identify());

		if(c.NandPatch)
			ciosPatcher.AddPatch(SimplePatch::FFS_PermsCheck());
			
		if(c.KoreanPatch)
		{
			ciosPatcher.AddPatch(&kkpatch);
			ciosPatcher.AddPatch(SimplePatch::KoreanKey_EnablePatch());
		}

		stringstream progressMessage;
		progressMessage << "Creating cIOS " << c.destId << "from IOS" << c.sourceId << "v" << c.revision;

		stringstream wadFile;
		wadFile << wadFolder << "/IOS" << c.sourceId << "v" << c.revision << ".wad";

		if(!File::Exists(wadFile.str()))
			throw Exception("File not found.", -1);

		cout << progressMessage.str() << endl;
		//OnProgress(progressMessage.str(), step/NB_INSTALL_CIOS);
		ciosPatcher.LoadFromWad(wadFile.str(), wadFolder);

		stringstream installMessage;
		installMessage << "Installing cIOS" << c.destId;
		cout << installMessage.str() << endl;
		//OnProgress(installMessage.str(), (step + 0.5)/NB_INSTALL_CIOS);
		ciosPatcher.Install();

		step += 1;
	}
}
