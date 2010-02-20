#include <sstream>
#include <iostream>
#include <iomanip>

#include <libutils/exception/Exception.h>
#include <libutils/fs/File.h>
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
        u32 shortId = (u32)ite->title;

        stringstream wadFile;
        stringstream wadName;

        if (type == 1)
            wadName << "IOS" << shortId << "v" << ite->revision << ".wad";
        else
            wadName << hex << setfill('0') << setw(8) <<  type << setw(0) << "-" << setw(8) << shortId << setw(0) << "v" << ite->revision << ".wad";
        if (type!=1 && Title::IsInstalled(ite->title))
        {
        if (Title::GetInstalledTitleVersion(ite->title)>=ite->revision)
            {
                continue;
            }
        }
        wadFile << Config::WorkingDirectory() << "/" << wadName.str();

        if (!File::Exists(wadFile.str()))
        {
        if (Config::HasNetwork())
            {
                Title t;

                stringstream downloadMessage;
                downloadMessage << "Downloading title " << shortId << " version " << ite->revision << " from NUS";
                OnProgress(downloadMessage.str(), step/nbIosToInstall);
                t.LoadFromNusServer(ite->title, ite->revision, Config::WorkingDirectory());

                stringstream packMessage;
                packMessage << "Saving it as " << wadName.str();
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
        u32 type = ite->title >> 32;
        u32 shortId = (u32)ite->title;

        stringstream wadFile;
        stringstream wadName;

        if (type == 1)
            wadName << "IOS" << shortId << "v" << ite->revision << ".wad";
        else
            wadName << hex << setfill('0') << setw(8) <<  type << setw(0) << "-" << setw(8) << shortId << setw(0) << "v" << ite->revision << ".wad";

        if (type!=1 && Title::IsInstalled(ite->title))
       {
        if (Title::GetInstalledTitleVersion(ite->title)>=ite->revision)
            {
                continue;
            }
        }
        wadFile << Config::WorkingDirectory() << "/" << wadName.str();

        if (!File::Exists(wadFile.str()))
        throw Exception("File not found.", -1);

        stringstream progressMessage;
        progressMessage << "Loading title " << shortId << " from Wad.";
        OnProgress(progressMessage.str(), step/nbIosToInstall);
        Title t;
        t.LoadFromWad(wadFile.str(), Config::WorkingDirectory());

        stringstream installMessage;
        installMessage << "Installing title " << shortId;
        OnProgress(installMessage.str(), (step + 0.5)/nbIosToInstall);
        t.Install();

        step += 1;
    }

OnProgress("System updated.", 1);
}
