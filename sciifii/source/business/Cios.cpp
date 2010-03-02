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

Cios::Cios(u32 iosId, u16 iosRevision, u32 slot, u16 ciosRevision)
: Installer(),
  _iosId(iosId),
  _iosRevision(iosRevision),
  _slot(slot),
  _ciosRevision(ciosRevision)
{}

void Cios::AddModule(ModuleDescriptor descriptor)
{
	_modules.push_back(descriptor);
}

void Cios::AddPlugin(PluginDescriptor descriptor)
{
	_plugins.push_back(descriptor);
}

void Cios::AddPatch(SimplePatch descriptor)
{
	_patches.push_back(descriptor);
}

bool Cios::Prepare()
{
	//TODO download source
	//TODO download modules
	//TOTO download plugins

	return true;
}

void Cios::Install()
{
	TitlePatcher cios(0x0000000100000000ULL + _slot, _ciosRevision);
	
	for(vector<SimplePatch>::iterator patch = _patches.begin(); patch != _patches.end(); patch++)
		cios.AddPatch(*patch);

	for(vector<PluginDescriptor>::iterator plugin = _plugins.begin(); plugin != _plugins.end(); plugin++)
	{
		Buffer plug = File::ReadToEnd(Config::WorkingDirectory() + "/" + plugin->moduleName + "_plugin.dat");
		PluginPatch plugPatch(plug, plugin->offset, plugin->bss, 0x2C000, plugin->moduleName);
		
		for(vector<SimplePatch>::iterator handle = plugin->handles.begin(); handle != plugin->handles.end(); handle++)
			plugPatch.DefineCommandHandle(*handle);
			
		cios.AddPatch(plugPatch);
	}
	
	for(vector<ModuleDescriptor>::iterator module = _modules.begin(); module != _modules.end(); module++)
		cios.AddModule(*module);


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
