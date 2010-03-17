#include "Preloader.h"

#include <libutils/fs/File.h>
#include <libutils/exception/Exception.h>
#include <malloc.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include "../../build/priiloader_dat.h"

using namespace std;

Preloader::Preloader()
        : bootCid(0)
{}

bool Preloader::Prepare()
{
    return true;
}

Buffer Preloader::GetSysMenuTMD()
{
    u32 tmd_size ATTRIBUTE_ALIGN(32);
    u64 title_id = 0x0000000100000002LL;

    s32 ret = ES_GetStoredTMDSize(title_id,&tmd_size);
    if (ret < 0)
        throw Exception("Unable to find System Menu TMD size.", ret);

    signed_blob *s_tmd = (signed_blob*)memalign(32,(tmd_size+32)&(~31));
    if (!s_tmd)
        throw Exception("Not enough memory!", -1);

    memset(s_tmd, 0, (tmd_size+32)&(~31));
    ret = ES_GetStoredTMD(title_id, s_tmd, tmd_size);
    if (ret < 0)
        throw Exception("Cant read SysMenu tmd!", -1);

    Buffer returnValue(s_tmd, (tmd_size+32)&(~31));
    free(s_tmd);

    return returnValue;
}

u32 Preloader::GetBootCid(tmd* t)
{
    for (u32 contentIndex = 0; contentIndex < t->num_contents; ++contentIndex)
        if (t->contents[contentIndex].index == t->boot_index)
            return t->contents[contentIndex].cid;

    return 0;
}

void Preloader::CopyTicket()
{
    if (!File::Exists("wii:/title/00000001/00000002/content/ticket"))
    {
        Buffer ticket = File::ReadToEnd("wii:/ticket/00000001/00000002.tik");
        File &f_tik = File::Create("wii:/title/00000001/00000002/content/ticket");
        try
        {
            f_tik.Write(ticket);
            f_tik.Close();
            delete &f_tik;
        }
        catch (...)
        {
            f_tik.Close();
            delete &f_tik;
            throw Exception("Error copying ticket!", -1);
        }
    }
}

void Preloader::CopySysMenu()
{
    stringstream menu;
    menu << "wii:/title/00000001/00000002/content/" << setw(8) << setfill('0') << hex << bootCid << ".app";

    stringstream copy;
    copy << "wii:/title/00000001/00000002/content/1" << setw(7) << setfill('0') << hex << bootCid << ".app";

    if (!File::Exists(copy.str()))
    {
        Buffer sysMenu = File::ReadToEnd(menu.str());
        File &f_sys = File::Create(copy.str());
        try
        {
            f_sys.Write(sysMenu);
            f_sys.Close();
            delete &f_sys;
        }
        catch (...)
        {
            f_sys.Close();
            delete &f_sys;
            throw Exception("Error copying SysMenu!", -1);
        }
    }
}

void Preloader::RestoreSysMenu()
{
    stringstream sysMenuApp;
    sysMenuApp << "wii:/title/00000001/00000002/content/" << setw(8) << setfill('0') << hex << bootCid << ".app";

    stringstream backup;
    backup << "wii:/title/00000001/00000002/content/1" << setw(7) << setfill('0') << hex << bootCid << ".app";

    Buffer b_backup = File::ReadToEnd(backup.str());

    if (File::Exists(sysMenuApp.str()))
        File::Delete(sysMenuApp.str());

    File &sysMenu = File::Create(sysMenuApp.str());
    sysMenu.Write(b_backup);
    sysMenu.Close();
    delete &sysMenu;
}

bool Preloader::CheckPreloader()
{

    stringstream sysMenuApp;
    sysMenuApp << "wii:/title/00000001/00000002/content/" << setw(8) << setfill('0') << hex << bootCid << ".app";

    Buffer copiedPloader = File::ReadToEnd(sysMenuApp.str());
    Buffer originalPloader(priiloader_dat, priiloader_dat_size);

    if (copiedPloader==originalPloader)
        return true;

    return false;
}

void Preloader::Install()
{
    //Getting boot index
    OnProgress("Getting sysMenu tmd.", 0.2);
    Buffer b_tmd = GetSysMenuTMD();
    tmd* tmd_data = (tmd*)SIGNATURE_PAYLOAD((signed_blob*)b_tmd.Content());

    OnProgress("Getting sysMenu boot index.", 0.3);
    bootCid = GetBootCid(tmd_data);
    if (bootCid == 0)
        throw Exception("Boot index not found!", -1);
    b_tmd.Clear();

    OnProgress("Copiing sysMenu ticket.", 0.4);
    CopyTicket();

    OnProgress("Copiing sysMenu.", 0.5);
    CopySysMenu();

    OnProgress("Deleting old preloader datas.", 0.6);
    File::Delete("wii:/title/00000001/00000002/data/loader.ini");

    stringstream sysMenuApp;
    sysMenuApp << "wii:/title/00000001/00000002/content/" << setw(8) << setfill('0') << hex << bootCid << ".app";

    try
    {
        OnProgress("Deleting sysMenu.", 0.7);
        File::Delete(sysMenuApp.str());

        OnProgress("Creating priiloader.", 0.8);
        Buffer originalPloader(priiloader_dat, priiloader_dat_size);
        File &ploader = File::Create(sysMenuApp.str());
        ploader.Write(originalPloader);
        ploader.Close();
        delete &ploader;

        //checking installation
        OnProgress("Checking Priiloader.", 0.9);
        if (!CheckPreloader())
            throw Exception("Error detected in priiloader.", -1);

        OnProgress("Priiloader installation done!", 1);
    }
    catch (Exception &ex)
    {
        RestoreSysMenu();
        OnProgress("Error, sysMenu restored.", 1);
        throw;
    }
    catch (...)
    {
        RestoreSysMenu();
        OnProgress("Error, sysMenu restored.", 1);
        throw;
    }
}