#include <sstream>
#include <iostream>
#include <iomanip>
#include <Libwiisys/system/Title.h>
#include <Libwiisys/IO/File.h>
#include <Libwiisys/IO/Directory.h>
#include <Libwiisys/IO/Path.h>
#include <Libwiisys/Exceptions/Exception.h>
#include <Libwiisys/logging/Log.h>
#include <sciifii/business/TitleStep.h>
#include <sciifii/business/common/FileManager.h>
#include <sciifii/Config.h>

using namespace std;
using namespace Libwiisys::Logging;
using namespace Libwiisys::Exceptions;
using namespace Libwiisys::System;
using namespace Libwiisys::System::Patching;
using namespace Libwiisys::IO;
using namespace Libwiisys::System::Event;
using namespace Libwiisys;


TitleStep::TitleStep(u64 titleId, u16 revision, TitleAction a, string path,Libwiisys::System::Patching::Fakesign_Type fakesign) :
    _id(titleId), _revision(revision), _action(a), _file(""),_key(""), _path(path),_fakesign(fakesign), _skipUpdate(false)
{}

TitleStep::TitleStep(string key, TitleAction a, string path,Libwiisys::System::Patching::Fakesign_Type fakesign) :
    _id(0), _revision(0), _action(a), _file(""),_key(key), _path(path),_fakesign(fakesign), _skipUpdate(false)
{}

bool TitleStep::Prepare()
{
  //reset the execution flags
  _skipUpdate = false;
  
  // Impossible to do from Wad files
  if (_action == ti_PackAsWad && _key != "")
    throw Exception("This is impossible to create a wad from an other wad!");
    
  if (_action == ti_PackAsWad && Path::GetFileExtension(_path) != "wad")
    throw Exception("You must specify a wad file path in order to store the wad");
  
  if (_action == ti_Extract && Path::GetFileExtension(_path) != "wad")
    throw Exception("You must specify a valid wad to put the extracted title");
	
  if (_action == ti_Decrypt && _path == "")
    throw Exception("You must specify a folder to store the decrypted title.");  
  
  if (_key != "") /* Si fichier donne en parametre */
  {
    OnProgress("Getting wad file : "+ _key, 0.25);
    if (!FileManager::Download(_key))
      throw Exception("Error downloading " + _key);

	_file = FileManager::GetPath(_key);
	Title ios;
	ios.LoadFromWad(_file);
	_id = ios.GetTitleId();
	_revision = ios.GetRevision();
  }
  else /* Si tid */
  {
    //skip downlload if the revision is already lower than the installed version
	if (_action == ti_Update && _revision != 0)
	  {
		if(Title::IsInstalled(_id) && _revision <= Title::GetInstalledTitleVersion(_id))
		{
		  OnProgress("Title update not necessary !", 1);
		  _skipUpdate = true;
		  return true;
		}
	  }
  
    if (_action!=ti_Uninstall && _action!=ti_Extract)
    {
      stringstream wad;
      wad << Config::WorkingDirectory() << "/" << Title::GetWadFormatedName(_id,_revision);
      _file = wad.str();

      if (!File::Exists(_file))
      {
        if (Config::HasNetwork())
        {
          Title ios;

          stringstream down;
          down << "Downloading title " << hex << setfill('0') << setw(16) << _id << dec;
          if ( _revision!=0)
            down << " version " << _revision;
          down << " from NUS.";

          OnProgress(down.str(), 0.25);
          ios.LoadFromNusServer(_id, _revision, Config::WorkingDirectory());

          stringstream pack;
          pack << "Saving as " << Path::GetFileName(_file);
          OnProgress(pack.str(), 0.75);
          ios.PackAsWad(_file);
		  _revision = ios.GetRevision();
        }
        else
        {
          cout << "You arent connected to the network and some wads are missing." << endl << "Please refer to the readme.";
          return false;
        }
      }
    }
  }
  
  if (_action == ti_Update)
  {
	if(Title::IsInstalled(_id) && _revision <= Title::GetInstalledTitleVersion(_id))
	{
	  OnProgress("Title update not necessary !", 1);
	  _skipUpdate = true;
	  return true;
	}
  }

  switch(_action)
  {
    case ti_Update:
		OnProgress("Title update preparation done!", 1);
		break;
    case ti_Extract:
		OnProgress("Title extraction preparation done!", 1);
		break;
    case ti_Decrypt:
		OnProgress("Title decryption preparation done!", 1);
		break;
	case ti_Uninstall:
		OnProgress("Title uninstallation preparation done!", 1);
		break;
	case ti_Install:
		OnProgress("Title installation preparation done!", 1);
		break;
	case ti_PackAsWad:
		OnProgress("Wad creation preparation done!", 1);
		break;
  }

  return true;
}

void TitleStep::Install()
{
  stringstream str;
  
  if (_action == ti_Update && !_skipUpdate)
  {
	TitlePatcher t(0,-1,_fakesign);

    if (_id == 0)
	{
      str << "Loading title from " << _file;
	}
    else
	{
      str << "Loading title  " << hex << setfill('0') << setw(16) << _id
      << dec;
	}
    OnProgress(str.str(), 0.25);
    t.LoadFromWad(_file, Config::WorkingDirectory());
    stringstream str2;
    if (_id == 0)
      str2 << "Updating title " << _file;
    else
      str2 << "Updating title  " << hex << setfill('0') << setw(16)
      << _id << dec;
    OnProgress(str2.str(), 0.75);
    t.Install();
  }
  else if (_action == ti_Uninstall)
  {
    str << "Uninstalling title " << hex << setfill('0') << setw(16) << _id
    << dec;
    OnProgress(str.str(), 0.25);
    Title::Uninstall(_id);
  }
  else if (_action == ti_Install)
  {
    TitlePatcher t(0,-1,_fakesign);

    if (_id == 0)
	{
      str << "Loading title from " << _file;
	}
    else
	{
      str << "Loading title  " << hex << setfill('0') << setw(16) << _id
      << dec;
	}
    OnProgress(str.str(), 0.25);
    t.LoadFromWad(_file, Config::WorkingDirectory());
    stringstream str2;
    if (_id == 0)
      str2 << "Installing title " << _file;
    else
      str2 << "Installing title  " << hex << setfill('0') << setw(16)
      << _id << dec;
    OnProgress(str2.str(), 0.75);
    t.Install();
  }
  else if (_action == ti_PackAsWad)
  {
    if (Path::GetParentDirectory(_path) != "")
      Directory::Create(Path::GetParentDirectory(_path));

    stringstream str2;
    str2 << "Moving  " << _file << " to " << _path;
    OnProgress(str2.str(), 0.50);
    File::Move(_file, _path);
  }
  else if (_action == ti_Extract)
  {
    Title t;
    str << "Extracting title  " << hex << setfill('0') << setw(16) << _id
    << dec;
    OnProgress(str.str(), 0.25);
    t.LoadFromNand(_id, Config::WorkingDirectory());

    stringstream str2;
    str2 << "Packing title  " << hex << setfill('0') << setw(16) << _id
    << dec;
    OnProgress(str2.str(), 0.75);
    t.PackAsWad(_path);
  }
  else if (_action == ti_Decrypt)
  {
    Title t;
    if (_id == 0)
      str << "Loading title from " << _file;
    else
      str << "Loading title  " << hex << setfill('0') << setw(16) << _id
      << dec;
    OnProgress(str.str(), 0.25);
    t.LoadFromWad(_file, Config::WorkingDirectory());
    stringstream str2;
    if (_id == 0)
      str2 << "Extracting content from " << _file << " to " << _path;
    else
      str2 << "Extracting title " << hex << setfill('0') << setw(16)
      << _id << dec << " contents";
    OnProgress(str2.str(), 0.75);
    t.SaveDecryptedContent(_path);

  }
 
  if (_action == ti_Uninstall)
    OnProgress("Title uninstallation done!", 1);
  else if (_action == ti_Install)
    OnProgress("Title installation  done!", 1);
  else if (_action == ti_PackAsWad)
    OnProgress("Wad creation done!", 1);
  else if (_action == ti_Decrypt)
    OnProgress("Title decrypted!", 1);
  else if (_action == ti_Extract)
    OnProgress("Title extracted!", 1);
}

void TitleStep::SendtoLog()
{
  stringstream str;
  str << "TitleStep(" << hex << _id << dec << "," << _revision << ","
  << _action << "," << _file << "," << _path << ")";
  Log::WriteLog(Log_Info, str.str());

}