#include "TitleStep.h"
#include "common/FileManager.h"
#include <libutils/system/Title.h>
#include <libutils/exception/Exception.h>
#include <sstream>
#include <libutils/fs/File.h>
#include <libutils/fs/Path.h>
#include <libutils/fs/Directory.h>
#include <libutils/system/Title.h>
#include "../Config.h"
#include <iostream>
#include <iomanip>

using namespace std;

TitleStep::TitleStep(u64 titleId, u16 revision, TitleAction a, string path) :_id(titleId),_revision(revision),_action(a),_file(""),_path(path)
{}

TitleStep::TitleStep(string file, TitleAction a, string path) :_id(0),_revision(0),_action(a),_file(file),_path(path)
{}

bool TitleStep::Prepare()
{
  if (_action == ti_PackAsWad && Path::GetFileExtension(_path) != "wad")
    throw Exception("You must specify a wad file path in order to store the wad", -1);

  if (_action == ti_PackAsWad && _file != "")
    throw Exception("This is impossible to create a wad from an other wad!", -1);

  if (_action == ti_Decrypt && _path == "")
    throw Exception("I don't know where to decrypt the title contents !", -1);

  if (_action == ti_Extract && Path::GetFileExtension(_path) != "wad")
    throw Exception("You must specify a wad file path in order to store the extracted title", -1);

  if (_action == ti_Extract && _file != "")
    throw Exception("This is impossible to extract a title from a wad!", -1);

  if (_file!="")  /* Si fichier donne en parametre */
    {
      OnProgress("Getting wad file", 0.25);
      if (!FileManager::Download(_file))
        throw Exception("Error downloading " + _file, -1);
      _file = FileManager::GetPath(_file);
    }
  else  /*  Si tid */
    {
      if (_action!=ti_Uninstall&& _action!=ti_Extract)
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
                    down << " version " << _revision ;
                  down << " from NUS.";

                  OnProgress(down.str(), 0.25);
                  ios.LoadFromNusServer(_id, _revision, Config::WorkingDirectory());

                  stringstream pack;
                  pack << "Saving as " << Path::GetFileName(_file);
                  OnProgress(pack.str(), 0.75);
                  ios.PackAsWad(_file);
                }
              else
                {
                  cout << "You arent connected to the network and some wads are missing." << endl << "Please refer to the readme.";
                  return false;
                }
            }
        }
    }

  if (_action == ti_Uninstall)
    OnProgress("Title uninstallation preparation done!", 1);
  else if (_action == ti_Install)
    OnProgress("Title installation preparation done!", 1);
  else if (_action == ti_PackAsWad)
    OnProgress("Wad creation preparation done!", 1);

  return true;
}

void TitleStep::Install()
{
  stringstream str;

  if (_action == ti_Uninstall && _id != 0)
    {
      str <<  "Uninstalling title "<<hex << setfill('0') << setw(16) << _id << dec;
      OnProgress(str.str(), 0.25);
      Title::Uninstall(_id);
    }
  else if (_action == ti_Uninstall && _id == 0)
    {
      Title t;
      str <<  "Loading title from "<<_file;
      OnProgress(str.str(), 0.25);
      t.LoadFromWad(_file);
      stringstream str2;
      str2 <<  "Uninstalling title "<<_file;
      OnProgress(str2.str(), 0.75);
      t.Uninstall();
    }
  else if (_action == ti_Install)
    {
      Title t;
      if (_id==0)  str <<  "Loading title from "<<_file;
      else  str <<  "Loading title  "<<hex << setfill('0') << setw(16) << _id << dec;
      OnProgress(str.str(), 0.25);
      t.LoadFromWad(_file);
      stringstream str2;
      if (_id==0)  str2 <<  "Installing title "<<_file;
      else  str2 <<  "Installing title  "<<hex << setfill('0') << setw(16) << _id << dec;
      OnProgress(str2.str(), 0.75);
      t.Install();
    }
  else if (_action == ti_PackAsWad )
    {
      if (Path::GetParentDirectory(_path) != "")
        Directory::Create(Path::GetParentDirectory(_path));

      stringstream str2;
      str2 <<  "Moving  "<<_file<<" to "<<_path;
      OnProgress(str2.str(), 0.50);
      File::Move(_file,_path);
    }
  else if (_action == ti_Extract )
    {
      Title t;
      str <<  "Extracting title  "<<hex << setfill('0') << setw(16) << _id << dec;
      OnProgress(str.str(), 0.25);
      t.LoadFromNand(_id);

      stringstream str2;
      str2 <<  "Packing title  "<<hex << setfill('0') << setw(16) << _id << dec;
      OnProgress(str2.str(), 0.75);
      t.PackAsWad(_path);
    }
  else if (_action == ti_Decrypt)
    {
      Title t;
      if (_id==0)  str <<  "Loading title from "<<_file;
      else  str <<  "Loading title  "<<hex << setfill('0') << setw(16) << _id << dec;
      OnProgress(str.str(), 0.25);
      t.LoadFromWad(_file);
      stringstream str2;
      if (_id==0)  str2 <<  "Extracting content from "<<_file<<" to "<<_path;
      else  str2 <<  "Extracting title "<<hex << setfill('0') << setw(16) << _id << dec<<" contents";
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

void  TitleStep::SendtoLog()
{
	stringstream str;
		str<<"TitleStep("<<hex<<_id<<dec<<","<<_revision<<","<<_action<<","<<_file<<","<<_path<<")";
		Log::WriteLog(Log_Info,str.str());

}
