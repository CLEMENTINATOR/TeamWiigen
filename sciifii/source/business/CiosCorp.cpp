#include "CiosCorp.h"

#include "../Config.h"
#include "common/KoreanKeyPatch.h"
#include "common/FileManager.h"

#include <iostream>
#include <sstream>

#include <libutils/com/NetworkRequest.h>
#include <libutils/exception/Exception.h>
#include <libutils/system/TitlePatcher.h>
#include <libutils/system/SimplePatch.h>
#include <libutils/system/ModulePatch.h>
#include <libutils/fs/File.h>
#include <libutils/fs/Path.h>

using namespace std;

void CiosCorp::AddItem(const ciosDesc& item)
{
  _items.push_back(item);
}

void CiosCorp::AddModule(const std::string& name, const moduleDesc& module)
{
  if (_modules.find(name) != _modules.end())
    throw Exception("The module has already been registered", -1);

  _modules.insert(pair<string,moduleDesc>(name, module));
}

bool CiosCorp::Prepare()
{
	f32 step = 0;
	u32 nbIosToInstall = _items.size() + _modules.size();

	for(vector<ciosDesc>::iterator ite = _items.begin(); ite != _items.end(); ++ite)
	{
		//pour ios pas sur nus
		if(ite->localOnly)
		{
			step++;
			continue;
		}
        u32 id=(u32) ite->sourceId;


		stringstream wadFile;
		wadFile << Config::WorkingDirectory() << "/" << Title::GetWadFormatedName( ite->sourceId,ite->revision);

		if(!File::Exists(wadFile.str()))
		{

			if(Config::HasNetwork())
			{
				Title ios;

				stringstream downloadMessage;
				downloadMessage << "Downloading IOS " << id << " version " << ite->revision << " from NUS";
				OnProgress(downloadMessage.str(), step/nbIosToInstall);
				ios.LoadFromNusServer(ite->sourceId, ite->revision, Config::WorkingDirectory());

				stringstream packMessage;
				packMessage << "Saving as " << Path::GetFileName(wadFile.str());
				OnProgress(packMessage.str(), (step + 0.5)/nbIosToInstall);
				ios.PackAsWad(wadFile.str());
			}
			else
			{
                cout << "Network unavailable and wad files missing. Please refer to the readme." << endl;
                return false;
			}
		}
		step += 1;
	}

	for(map<string, moduleDesc>::iterator ite = _modules.begin(); ite != _modules.end(); ite++)
	{
		OnProgress("Downloading " + ite->second.file, step/nbIosToInstall);
		FileManager::Download(ite->second.file);
		OnProgress(ite->second.file+ " downloaded", (step + 0.5)/nbIosToInstall);
		step++;
	}

	OnProgress("Cioscorp preparation done.", 1);

	return true;
}

void CiosCorp::Install()
{
	map<string, ModulePatch*> moduleList;

	KoreanKeyPatch kkpatch;

	f32 step = 0;
	u32 nbIosToInstall = _items.size();

	try
	{
		for(vector<ciosDesc>::iterator ite = _items.begin(); ite != _items.end(); ++ite)
		{
			stringstream wadFile;
			wadFile << Config::WorkingDirectory() << "/" << Title::GetWadFormatedName( ite->sourceId,ite->revision);

			if(!File::Exists(wadFile.str()) && !ite->localOnly)
				throw Exception("File not found.", -1);
			else if(!File::Exists(wadFile.str()))
				continue;

			TitlePatcher ciosPatcher( ite->destId, 0xFFFF);
			u32 destid= (u32)ite->destId;
			u32 srcid=(u32)ite->sourceId ;
			ciosPatcher.AddPatch(SimplePatch::ES_HashCheck_Old());
			ciosPatcher.AddPatch(SimplePatch::ES_HashCheck_New());

			for(vector<string>::iterator mod = ite->modules.begin(); mod != ite->modules.end(); mod++)
			{
				if(moduleList.find(*mod) == moduleList.end())
				{
					moduleDesc desc = _modules.find(*mod)->second;
					Buffer bmod = FileManager::GetFile(desc.file);
					ModulePatch* pmod = new ModulePatch((u8*)bmod.Content(), bmod.Length(), desc.module);
					moduleList.insert(pair<string, ModulePatch*>(*mod, pmod));
				}

				ciosPatcher.AddPatch(moduleList.find(*mod)->second);
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
			progressMessage << "Creating cIOS" << destid << " from IOS" << srcid << "v" << ite->revision;
			OnProgress(progressMessage.str(), step/nbIosToInstall);
			ciosPatcher.LoadFromWad(wadFile.str(), Config::WorkingDirectory());

			stringstream installMessage;
			installMessage << "Installing cIOS" <<destid;
			OnProgress(installMessage.str(), (step + 0.5)/nbIosToInstall);
			ciosPatcher.Install();

			step += 1;
		}
	}
	catch(Exception &ex)
	{
		for(map<string, ModulePatch*>::iterator ite = moduleList.begin(); ite != moduleList.end(); ite++)
			delete ite->second;
		throw;
	}
	catch(...)
	{
		for(map<string, ModulePatch*>::iterator ite = moduleList.begin(); ite != moduleList.end(); ite++)
			delete ite->second;
		throw;
	}

	for(map<string, ModulePatch*>::iterator ite = moduleList.begin(); ite != moduleList.end(); ite++)
		delete ite->second;

	OnProgress("Cioscorp installed.", 1);
}
