#include "Cios.h"
#include "../Config.h"

#include <libwiisys.h>

#include <sstream>
#include "common/FileManager.h"

using namespace std;
using namespace Libwiisys;
using namespace Libwiisys::Network;
using namespace Libwiisys::Logging;
using namespace Libwiisys::Serialization;
using namespace Libwiisys::String;
using namespace Libwiisys::Exceptions;
using namespace Libwiisys::IO;
using namespace Libwiisys::System;
using namespace Libwiisys::System::Patching;


Cios::Cios(u32 iosId, u16 iosRevision, u32 slot, u16 ciosRevision)
: Installer(),
  _iosId(iosId),
  _iosRevision(iosRevision),
  _slot(slot),
  _ciosRevision(ciosRevision)
{}

void Cios::AddModule(customModule descriptor)
{
	_modules.push_back(descriptor);
}

void Cios::AddPlugin(pluginDescriptor descriptor)
{
	_plugins.push_back(descriptor);
}

void Cios::AddPatch(Patch* descriptor)
{
	_patches.push_back(descriptor);
}

bool Cios::Prepare()
{
	stringstream wadFile;
	wadFile << Config::WorkingDirectory() << "/" << Title::GetWadFormatedName( 0x100000000ULL + _iosId, _iosRevision);
    OnProgress("Downloading base ios.", 0.2);
	if(!File::Exists(wadFile.str()))
	{
		if(Config::HasNetwork())
		{
			Title ios;
			ios.LoadFromNusServer(0x100000000ULL + _iosId, _iosRevision, Config::WorkingDirectory());
			ios.PackAsWad(wadFile.str());
		}
		else
		{
			cout << "Network unavailable and wad files missing. Please refer to the readme." << endl;
			return false;
		}
	}
    OnProgress("Downloading plugins.", 0.5);
	for(vector<pluginDescriptor>::iterator plugin = _plugins.begin(); plugin != _plugins.end(); plugin++)
	{
		FileManager::Download(plugin->file);
	}

    OnProgress("Downloading custum modules.", 0.7);

	for(vector<customModule>::iterator ite = _modules.begin(); ite != _modules.end(); ite++)
	{
        FileManager::Download(ite->file);
	}

    OnProgress("cIOS preparation done !", 1);
	return true;
}

void Cios::Install()
{
	TitlePatcher cios(0x0000000100000000ULL + _slot, _ciosRevision);

	vector<Patch*> toDelete;

	try
	{

		for(vector<Patch*>::iterator patch = _patches.begin(); patch != _patches.end(); patch++)
		{
			cios.AddPatch(*patch);
		}

		for(vector<pluginDescriptor>::iterator plugin = _plugins.begin(); plugin != _plugins.end(); plugin++)
		{
			Buffer plug = FileManager::GetFile(plugin->file);
			PluginPatch* plugPatch = NULL;
			
			if(!plugin->replaceSection)
				plugPatch = new PluginPatch(plug, plugin->offset, plugin->bss, plugin->moduleName);
			else
				plugPatch = new PluginPatch(plug, plugin->header, plugin->moduleName, plugin->segment);

			for(vector<SimplePatch>::iterator handle = plugin->handles.begin(); handle != plugin->handles.end(); handle++)
				plugPatch->DefineCommandHandle(*handle);

			cios.AddPatch(plugPatch);
			toDelete.push_back(plugPatch);
		}

        for(vector<customModule>::iterator module = _modules.begin(); module != _modules.end(); module++)
		{
			Buffer bmod = FileManager::GetFile(module->file);
			TitleModule tmodule(bmod, module->position);
			cios.AddModule(tmodule);
		}


		stringstream wadFile;
		wadFile << Config::WorkingDirectory() << "/" << Title::GetWadFormatedName(0x0000000100000000ULL + _iosId, _iosRevision);
        stringstream str;
        str<<"Deleting old IOS"<<_slot<<" or stub";
		OnProgress(str.str(), 0.2);
		Title::Uninstall(0x0000000100000000ULL + _slot);

		OnProgress("Load base wad for cios and patch it!", 0.4);
		cios.LoadFromWad(wadFile.str(), Config::WorkingDirectory());

		OnProgress("Installation of the cIOS!", 0.8);
		cios.Install();

		OnProgress("cIOS installed.", 1);
	}
	catch(Exception &ex)
	{
		for(vector<Patch*>::iterator ite = toDelete.begin(); ite != toDelete.end(); ite++)
			delete *ite;

		throw;
	}
	catch(...)
	{
		for(vector<Patch*>::iterator ite = toDelete.begin(); ite != toDelete.end(); ite++)
			delete *ite;

		throw;
	}

	for(vector<Patch*>::iterator ite = toDelete.begin(); ite != toDelete.end(); ite++)
		delete *ite;
}

void Cios::SendToLog()
{
stringstream str;
str<<"Cios("<<_iosId<<","<<_iosRevision<<","<<_slot<<","<<_ciosRevision<<")";
Log::WriteLog(Log_Info,str.str());
}
