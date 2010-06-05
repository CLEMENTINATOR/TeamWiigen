#include "TitleDowngrader.h"
#include <sstream>
#include <libutils/fs/File.h>
#include <libutils/fs/Path.h>
#include <libutils/exception/Exception.h>
#include <libutils/system/Title.h>
#include "../Config.h"
#include <iostream>

using namespace fastdelegate;
using namespace std;

TitleDowngrader::TitleDowngrader(u64 titleId, u16 neededRevision)
    : _id(titleId),
    _neededRevision(neededRevision)
{}

bool TitleDowngrader::Prepare()
{

  stringstream newWad;
  newWad << Config::WorkingDirectory() << "/"<<Title::GetWadFormatedName(_id,0);

  stringstream oldWad;
  oldWad << Config::WorkingDirectory() << "/" <<Title::GetWadFormatedName(_id,_neededRevision);

  if ((!File::Exists(newWad.str()) || !File::Exists(oldWad.str())) && !Config::HasNetwork())
    {
      cout << "Network unavailable and wad files missing. Please refer to the readme." << endl;
      return false;
    }

  if (!File::Exists(newWad.str()))
    {
      Title ios;

      stringstream downloadMessage;
      downloadMessage << "Downloading title " <<hex<<setfill('0') << setw(16) << _id << dec<< " from NUS.";
      OnProgress(downloadMessage.str(), 0);
      ios.LoadFromNusServer(_id, 0, Config::WorkingDirectory());

      stringstream packMessage;
      packMessage << "Saving as "<< Path::GetFileName(newWad.str());
      OnProgress(packMessage.str(), 0.25);
      ios.PackAsWad(newWad.str());
    }

  if (!File::Exists(oldWad.str()))
    {
      Title ios;

      stringstream downloadMessage;
      downloadMessage << "Downloading title " << hex<<setfill('0') << setw(16)<< _id << dec<< "v" << _neededRevision << " from NUS.";
      OnProgress(downloadMessage.str(), 0.5);
      ios.LoadFromNusServer(_id, _neededRevision, Config::WorkingDirectory());

      stringstream packMessage;
      packMessage << "Saving as " << Path::GetFileName(oldWad.str());
      OnProgress(packMessage.str(), 0.75);
      ios.PackAsWad(oldWad.str());
    }

  OnProgress("Downgrade preparation done.", 1);
  return true;
}

void TitleDowngrader::Install()
{
  stringstream oldFile;
  oldFile << Config::WorkingDirectory() << "/" << Title::GetWadFormatedName(_id,_neededRevision);

  stringstream newFile;
  newFile<< Config::WorkingDirectory() << "/" << Title::GetWadFormatedName(_id,0);

  Title newTitle;
  newTitle.TmdInstalledEvent += MakeDelegate(this, &TitleDowngrader::DowngradeTmd);

  newTitle.LoadFromWad(newFile.str() , "sd:/temp");

  Title oldTitle;
  oldTitle.TicketInstallingEvent += MakeDelegate(this, &TitleDowngrader::SkipStep);
  oldTitle.LoadFromWad(oldFile.str(), "sd:/temp");

  OnProgress("Installing the fake title", 0.2);

  //this will be aborted by the event handler
  try
  {
    newTitle.Install();
  }
  catch (Exception &ex)
  {
    throw;
  }
  OnProgress("Installing the good title.",0.6);
  //this will install the needed revision
  oldTitle.Install();

  OnProgress("Title downgraded !", 1);
}

void TitleDowngrader::DowngradeTmd(Object* sender, TitleEventArgs *args)
{
  OnProgress("Downgrading tmd.", 0.4);
  string tmd_path = "wii:/tmp/title.tmd";
  File::Delete(tmd_path);

  u8 *ptmd = (u8*) (args->buffer.Content());

  ptmd[0x1dc] = 0; //set revision to 0
  ptmd[0x1dd] = 0; // set the content number to 0

  File &f_tmd = File::Create(tmd_path);
  f_tmd.Write(args->buffer);
  f_tmd.Close();
  delete &f_tmd;

  ES_AddTitleFinish();

  args->abortProcess = true;
}

void TitleDowngrader::SkipStep(Object* sender, TitleEventArgs *args)
{
  OnProgress("Skipping ticket installation.", 0.8);
  args->skipStep = true;
}
