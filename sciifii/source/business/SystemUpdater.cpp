#include <sstream>
#include <iostream>
#include <iomanip>

#include <libutils/exception/Exception.h>
#include <libutils/fs/File.h>
#include <libutils/fs/Path.h>
#include <libutils/system/Title.h>

#include "SystemUpdater.h"

using namespace std;

bool SystemUpdater::Prepare()
{
    f32 step = 0;

    vector<titleDescriptor> titles = Config::UpdateConfiguration();
    u32 nbIosToInstall = titles.size();

    for (vector<titleDescriptor>::iterator ite = titles.begin(); ite != titles.end(); ++ite)
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
                cout << "You arent connected to the network and some wads are missing." << endl
                << "Please refer to the readme.";
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

    vector<titleDescriptor> titles = Config::UpdateConfiguration();
    u32 nbIosToInstall = titles.size();

    for (vector<titleDescriptor>::iterator ite = titles.begin(); ite != titles.end(); ++ite)
    {

        stringstream wadFile;
        wadFile << Config::WorkingDirectory() << "/" << Title::GetWadFormatedName(ite->title,ite->revision);

        if (!File::Exists(wadFile.str()))
            throw Exception("File not found.", -1);

        stringstream progressMessage;
        progressMessage << "Loading title " <<hex<<setfill('0')<<setw(16)<<ite->title<<dec<<" version "<<ite->revision<< " from Wad.";
        OnProgress(progressMessage.str(), step/nbIosToInstall);
        Title t;
        t.LoadFromWad(wadFile.str(), Config::WorkingDirectory());

        stringstream installMessage;
        installMessage << "Installing title " <<hex<<setfill('0')<<setw(16)<<ite->title<<dec<<".";
        OnProgress(installMessage.str(), (step + 0.5)/nbIosToInstall);
        t.Install();

        step += 1;
    }

    OnProgress("System updated.", 1);
}
