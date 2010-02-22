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

bool CiosCorp::Prepare()
{
	f32 step = 0;
	vector<ciosDesc> corp = Config::CorpConfiguration();
	u32 nbIosToInstall = corp.size();

	for(vector<ciosDesc>::iterator ite = corp.begin(); ite != corp.end(); ++ite)
	{
		//pour ios pas sur nus
		if(ite->localOnly)
		{
			step++;
			continue;
		}

		u64 source = 0x0000000100000000ULL + ite->sourceId;

		stringstream wadFile;
		wadFile << Config::WorkingDirectory() << "/" << Title::GetWadFormattedName(source,ite->revision);

		if(!File::Exists(wadFile.str()))
		{

			if(Config::HasNetwork())
			{
				Title ios;

				stringstream downloadMessage;
				downloadMessage << "Downloading IOS " << ite->sourceId << " version " << ite->revision << " from NUS";
				OnProgress(downloadMessage.str(), step/nbIosToInstall);
				ios.LoadFromNusServer(source, ite->revision, Config::WorkingDirectory());

				stringstream packMessage;
				packMessage << "Saving as " <<Title::GetWadFormattedName(source,ite->revision);
				OnProgress(packMessage.str(), (step + 0.5)/nbIosToInstall);
				ios.PackAsWad(wadFile.str());
			}
			else
			{
				cout << "You arent connected to the network and some wads are missing." << endl
				     << "Please refer to the readme.";
				return false;
			}
		}
		step += 1;
	}

	OnProgress("Cioscorp preparation done.", 1);

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
	vector<ciosDesc> corp = Config::CorpConfiguration();
	u32 nbIosToInstall = corp.size();

	for(vector<ciosDesc>::iterator ite = corp.begin(); ite != corp.end(); ++ite)
	{
		stringstream wadFile;
		wadFile << Config::WorkingDirectory() << "/" << Title::GetWadFormattedName(0x0000000100000000ULL + ite->sourceId,ite->revision);

		if(!File::Exists(wadFile.str()) && !ite->localOnly)
			throw Exception("File not found.", -1);
		else if(!File::Exists(wadFile.str()))
			continue;

		u64 dest = 0x0000000100000000ULL + ite->destId;

		TitlePatcher ciosPatcher(dest, 0xFFFF);

		ciosPatcher.AddPatch(SimplePatch::ES_HashCheck_Old());
		ciosPatcher.AddPatch(SimplePatch::ES_HashCheck_New());

		switch(ite->dipVersion)
		{
			case 13:
				ciosPatcher.AddPatch(&dip13);
				break;
			case 17:
				ciosPatcher.AddPatch(&dip17);
				break;
		}

		switch(ite->esVersion)
		{
			case 17:
				ciosPatcher.AddPatch(&es17);
				break;
		}

		if(ite->IdentifyPatch)
			ciosPatcher.AddPatch(SimplePatch::ES_Identify());

		if(ite->NandPatch)
			ciosPatcher.AddPatch(SimplePatch::FFS_PermsCheck());

		if(ite->KoreanPatch)
		{
			ciosPatcher.AddPatch(&kkpatch);
			ciosPatcher.AddPatch(SimplePatch::KoreanKey_EnablePatch());
		}

		stringstream progressMessage;
		progressMessage << "Creating cIOS" << ite->destId << " from IOS" << ite->sourceId << "v" << ite->revision;
		OnProgress(progressMessage.str(), step/nbIosToInstall);
		ciosPatcher.LoadFromWad(wadFile.str(), Config::WorkingDirectory());

		stringstream installMessage;
		installMessage << "Installing cIOS" << ite->destId;
		OnProgress(installMessage.str(), (step + 0.5)/nbIosToInstall);
		ciosPatcher.Install();

		step += 1;
	}

	OnProgress("Cioscorp installed.", 1);
}
