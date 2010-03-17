#include "TitleStep.h"
#include "common/FileManager.h"
#include <libutils/system/Title.h>
#include <libutils/exception/Exception.h>
#include <sstream>
#include <libutils/fs/File.h>
#include <libutils/fs/Path.h>
#include <libutils/system/Title.h>
#include "../Config.h"
#include <iostream>
#include <iomanip>

using namespace std;

TitleStep::TitleStep(u64 titleId, u16 revision, TitleAction a) :_id(titleId),_revision(revision),_action(a),_file(""),_path("")
{}

TitleStep::TitleStep(string file,string path,TitleAction a) :_id(0),_revision(0),_action(a),_file(file),_path(path)
{}

bool TitleStep::Prepare()
{
  if (_file!="")  /* Si fichier donne en parametre */
    {
      OnProgress("Getting wad file", 0.25);
      if (!FileManager::Download(_file))
        throw Exception("Error downloading " + _file, -1);
      _file = FileManager::GetPath(_file);
    }
  else  /*  Si tid */
    {
      if (_action!=ti_Uninstall)
        {
          stringstream wad;
          wad << Config::WorkingDirectory() << "/" << Title::GetWadFormatedName(_id,_revision);

          if (!File::Exists(wad.str()))
            {
              if (Config::HasNetwork())
                {
                  Title ios;

                  stringstream down;
                  down << "Downloading title " << hex << setfill('0') << setw(16) << _id << dec;
                  if ( _revision!=0) down<< " version " << _revision ;
                  down << " from NUS.";
                  OnProgress(down.str(), 0.25);
                  ios.LoadFromNusServer(_id, 0, Config::WorkingDirectory());

                  stringstream pack;
                  pack << "Saving as " << Path::GetFileName(wad.str());
                  OnProgress(pack.str(), 0.75);
                  ios.PackAsWad(wad.str());
                  _file = wad.str();
                }
              else
                {
                  cout << "You arent connected to the network and some wads are missing." << endl
                  << "Please refer to the readme.";
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
  if (_action == ti_Uninstall && _id != 0)
    {
      Title::Uninstall(_id);
    }
  else if (_action == ti_Uninstall && _id == 0)
    {
      Title t;
      t.LoadFromWad(_file);
      t.Uninstall();
    }
  else if (_action == ti_Install)
    {
      Title t;
      t.LoadFromWad(_file);
      t.Install();
    }
  else if (_action == ti_PackAsWad )
    {
      if (_path!="")
        {
          stringstream str;
          stringstream newFilePath;
          str<<Config::WorkingDirectory()<<"/";
          if (_file!="")  str<<_file;
          else str<<Title::GetWadFormatedName(_id,_revision);

          newFilePath<<_path<<"/";
          if (_file!="") newFilePath<<_file;
          else  newFilePath<<Title::GetWadFormatedName(_id,_revision);
          Buffer b=File::ReadToEnd(str.str());
          File &f=File::Create(newFilePath.str());
          f.Write(b);
          f.Close();
          delete &f;
        }
    }
}
