#include <sstream>
#include <iostream>
#include <iomanip>

#include <libwiisys.h>

#include "SystemUpdater.h"

using namespace std;
using namespace Libwiisys::Logging;
using namespace Libwiisys::Exceptions;
using namespace Libwiisys::System;
using namespace Libwiisys::System::Patching;
using namespace Libwiisys::IO;
void SystemUpdater::AddTitle(const titleDescriptor& descriptor)
{
		_updateTitles.push_back(descriptor);
}

bool SystemUpdater::Prepare()
{
    f32 step = 0;

    u32 nbIosToInstall = _updateTitles.size();

    for (vector<titleDescriptor>::iterator ite = _updateTitles.begin(); ite != _updateTitles.end(); ++ite)
    {
        u32 type = ite->title >> 32;

        if (type!=1 && Title::IsInstalled(ite->title))
        {
            if (Title::GetInstalledTitleVersion(ite->title)>=ite->revision)
            {
                step+=1;
                continue;
            }
        }

		stringstream wadFile;

        wadFile << Config::WorkingDirectory() << "/" << Title::GetWadFormatedName(ite->title,ite->revision);

        if (!File::Exists(wadFile.str()))
        {
            if (Config::HasNetwork())
            {
                Title t;

                stringstream downloadMessage;
                downloadMessage << "Downloading title " <<hex<<setfill('0')<<setw(16)<<ite->title<<dec<<" version " << ite->revision << " from NUS";
                OnProgress(downloadMessage.str(), step/nbIosToInstall);
                t.LoadFromNusServer(ite->title, ite->revision, Config::WorkingDirectory());

                stringstream packMessage;
                packMessage << "Saving it as " << Path::GetFileName(wadFile.str());
                OnProgress(packMessage.str(), (step + 0.5)/nbIosToInstall);
                t.PackAsWad(wadFile.str());
            }
            else
            {
                cout << "Network unavailable and wad files missing. Please refer to the readme." << endl;
                return false;
            }
        }
        step += 1;
    }

    OnProgress("System update preparation done.", 1);

    return true;
}

void SystemUpdater::Install()
{
    f32 step = 0;

    u32 nbIosToInstall = _updateTitles.size();

    for (vector<titleDescriptor>::iterator ite = _updateTitles.begin(); ite != _updateTitles.end(); ++ite)
    {

        stringstream wadFile;
        wadFile << Config::WorkingDirectory() << "/" << Title::GetWadFormatedName(ite->title,ite->revision);

        if (!File::Exists(wadFile.str()))
            throw Exception("File not found.", -1);

        stringstream progressMessage;
        progressMessage << "Loading title " <<hex<<setfill('0')<<setw(16)<<ite->title<<dec<<" version "<<ite->revision<< " from Wad.";
        OnProgress(progressMessage.str(), step/nbIosToInstall);
        TitlePatcher t(ite->slot);
        t.LoadFromWad(wadFile.str(), Config::WorkingDirectory());

        stringstream installMessage;
        installMessage << "Installing title " <<hex<<setfill('0')<<setw(16)<<ite->title<<dec<<".";
        OnProgress(installMessage.str(), (step + 0.5)/nbIosToInstall);
        t.Install();

        step += 1;
    }

    OnProgress("System updated.", 1);
}
void SystemUpdater::SendToLog()
{
  Log::WriteLog(Log_Info,"SystemUpdater()");
  for (vector<titleDescriptor>::iterator ite = _updateTitles.begin(); ite != _updateTitles.end(); ++ite)
  {
    stringstream s;
    s<<"SystemUpdaterItem("<<hex<<ite->slot<<","<<ite->title<<","<<dec<<ite->revision<<","<<ite->onlyOnUninstall<<")";
    Log::WriteLog(Log_Info,s.str());
  }
  Log::WriteLog(Log_Info,"End of SystemUpdater()");
}
