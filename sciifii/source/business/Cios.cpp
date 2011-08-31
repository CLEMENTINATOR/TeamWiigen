#include <sstream>
#include <iostream>
#include <Libwiisys/system/Patching/PluginPatch.h>
#include <Libwiisys/system/Title.h>
#include <Libwiisys/IO/File.h>
#include <sciifii/business/Cios.h>
#include <sciifii/Config.h>
#include <Libwiisys/logging/Log.h>
#include <sciifii/business/common/FileManager.h>
#include <Libwiisys/system/Patching/TitlePatcher.h>
#include <Libwiisys/Exceptions/Exception.h>

using namespace std;
using namespace Libwiisys;
using namespace Libwiisys::Logging;
using namespace Libwiisys::Serialization;
using namespace Libwiisys::Exceptions;
using namespace Libwiisys::IO;
using namespace Libwiisys::System;
using namespace Libwiisys::System::Patching;


Cios::Cios(u32 iosId, u16 iosRevision, u32 slot, s32 ciosRevision, string bannerFile, bool del)
    : Installer(),
    _iosId(iosId),
    _iosRevision(iosRevision),
    _slot(slot),
    _ciosRevision(ciosRevision),
	_bannerFile(bannerFile),
    _delete(del)	
{}

void Cios::AddModule(customModule descriptor)
{
  _modules.push_back(descriptor);
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

  OnProgress("Downloading custum modules.", 0.5);

  for(vector<customModule>::iterator ite = _modules.begin(); ite != _modules.end(); ite++)
  {
    FileManager::Download(ite->file);
  }
  
  if(_bannerFile != "")
	FileManager::Download(_bannerFile);

  OnProgress("cIOS preparation done !", 1);
  return true;
}

void Cios::Install()
{
  TitlePatcher cios(0x0000000100000000ULL + _slot, _ciosRevision);

    for(vector<Patch*>::iterator patch = _patches.begin(); patch != _patches.end(); patch++)
      cios.AddPatch(*patch);

    for(vector<customModule>::iterator module = _modules.begin(); module != _modules.end(); module++)
    {
      Buffer bmod = FileManager::GetFile(module->file);
      TitleModule tmodule(bmod, module->position);
      cios.AddModule(tmodule);
    }

	if(_bannerFile != "")
	{
		Buffer banner = FileManager::GetFile(_bannerFile);
		cios.DefineNewBanner(banner);
	}

    stringstream wadFile;
    wadFile << Config::WorkingDirectory() << "/" << Title::GetWadFormatedName(0x0000000100000000ULL + _iosId, _iosRevision);
    if(_delete)
    {
      stringstream str;
      str<<"Deleting old IOS"<<_slot<<" or stub";
      OnProgress(str.str(), 0.2);
      Title::Uninstall(0x0000000100000000ULL + _slot);
    }

    OnProgress("Load base wad for cios and patch it!", 0.4);
    cios.LoadFromWad(wadFile.str(), Config::WorkingDirectory());

    OnProgress("Installation of the cIOS!", 0.8);
    cios.Install();

    OnProgress("cIOS installed.", 1);
}

void Cios::SendToLog()
{
  stringstream str;
  str<<"Cios("<<_iosId<<","<<_iosRevision<<","<<_slot<<","<<_ciosRevision<<")";
  Log::WriteLog(Log_Info,str.str());
}

Cios::~Cios()
{
  for(vector<Patch*>::iterator ite = _patches.begin(); ite != _patches.end(); ite++)
    delete *ite;
}
