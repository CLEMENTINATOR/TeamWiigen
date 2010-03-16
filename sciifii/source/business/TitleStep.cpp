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

TitleStep::TitleStep(u64 titleId, u16 revision,TitleAction a) :_id(titleId),_revision(revision),_action(a),_file("")
{}
TitleStep::TitleStep(std::string file,TitleAction a) : _id(0),_revision(0),_action(a),_file(file)
{}

bool TitleStep::Prepare()
{
  if (_file!="")  /* Si fichier donne en parametre */
    {
      if (!FileManager::Download(_file))
        throw Exception("Error downloading " + _file, -1);
      return true;
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
                }
              else
                {
                  cout << "You arent connected to the network and some wads are missing." << endl
                  << "Please refer to the readme.";
                  return false;
                }
            }

          OnProgress("Title installation preparation done.", 1);
          return true;
        }
      else
        {
          OnProgress("Title uninstallation preparation done.", 1);
          return true; /* Si action = uninstall, pas de preparation */
        }

    }

}

void TitleStep::Install()
{
  Title t;
  if (_action==ti_PackAsWad) return;

  if (_file!="") /*  Si provient d'un fichier */
    {
      string wadPath = FileManager::GetPath(_file);
      t.LoadFromWad(wadPath);
      if (_action==ti_Install) t.Install();
      else t.Uninstall();

    }
  else /* Si provient de NUS */
    {
      if (_action==ti_Install)
        {
          stringstream wadPath;
          wadPath << Config::WorkingDirectory() << "/" << Title::GetWadFormatedName(_id,_revision);
          t.LoadFromWad(wadPath.str());
          t.Install();
        }
      else t.Uninstall(_id);
    }

}
