#include "Cios.h"
#include "../Config.h"

#include <libutils/fs/File.h>
#include <libutils/fs/Path.h>
#include <libutils/system/Title.h>
#include <libutils/system/TitlePatcher.h>
#include <libutils/system/PluginPatch.h>
#include <libutils/exception/Exception.h>
#include <libutils/com/NetworkRequest.h>

#include <sstream>
#include "common/FileManager.h"

using namespace std;

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
			cout << "You arent connected to the network and some wads are missing." << endl
				 << "Please refer to the readme.";
			return false;
		}
	}

	for(vector<pluginDescriptor>::iterator plugin = _plugins.begin(); plugin != _plugins.end(); plugin++)
	{
		FileManager::Download(plugin->file);
	}

	for(vector<customModule>::iterator ite = _modules.begin(); ite != _modules.end(); ite++)
	{
        FileManager::Download(ite->name);
	}

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
			Buffer plug = File::ReadToEnd(Config::WorkingDirectory() + "/" + plugin->moduleName + "_plugin.dat");
			PluginPatch* plugPatch = new PluginPatch(plug, plugin->offset, plugin->bss, plugin->moduleName);

			for(vector<SimplePatch>::iterator handle = plugin->handles.begin(); handle != plugin->handles.end(); handle++)
				plugPatch->DefineCommandHandle(*handle);

			cios.AddPatch(plugPatch);
			toDelete.push_back(plugPatch);
		}

        for(vector<customModule>::iterator module = _modules.begin(); module != _modules.end(); module++)
		{
			Buffer bmod = FileManager::GetFile(module->name);
			TitleModule tmodule((u8*)bmod.Content(),bmod.Length(), module->position);
			cios.AddModule(tmodule);
		}


		stringstream wadFile;
		wadFile << Config::WorkingDirectory() << "/" << Title::GetWadFormatedName(0x0000000100000000ULL + _iosId, _iosRevision);

		OnProgress("Deleting old IOS249 or stub.", 0.2);
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
