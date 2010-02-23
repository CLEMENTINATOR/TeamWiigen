#include "LoaderGX.h"
#include "../Config.h"
#include <libutils/com/NetworkRequest.h>
#include <libutils/fs/Directory.h>
#include <libutils/fs/File.h>
#include <libutils/system/Title.h>

using namespace std;

LoaderGX::LoaderGX()
{
	_language = GetLanguage();
}

string LoaderGX::GetLanguage()
{	
	switch(CONF_GetLanguage())
	{
		case CONF_LANG_JAPANESE:
			return"japanese.lang";
		case CONF_LANG_GERMAN:
			return"german.lang";
		case CONF_LANG_FRENCH:
			return"french.lang";
		case CONF_LANG_SPANISH:
			return"spanish.lang";
		case CONF_LANG_ITALIAN:
			return"italian.lang";
		case CONF_LANG_DUTCH:
			return"dutch.lang";
		case CONF_LANG_SIMP_CHINESE:
			return"schinese.lang";
		case CONF_LANG_TRAD_CHINESE:
			return"tchinese.lang";
		case CONF_LANG_KOREAN:
			return"korean.lang";
		case CONF_LANG_ENGLISH:
		default:
			return"english.lang";
	}	
}

bool LoaderGX::Prepare()
{
	OnProgress("Creating directories", 0.1);
	Directory::Create("sd:/apps/usbloader_gx");
	Directory::Create("sd:/codes");
	Directory::Create("sd:/txtcodes");
	Directory::Create("sd:/images/disc");
	Directory::Create("sd:/config/backgroundmusic");
	Directory::Create("sd:/config/language");
	
	string langFile = "http://usbloader-gui.googlecode.com/svn/trunk/Languages/" + _language;
	string sdLangFile = "sd:/config/language/" + _language;
	
	OnProgress("Obtain language file.", 0.2);
	if(!File::Exists(sdLangFile))
	{
		NetworkRequest req(langFile);
		Buffer response = req.GetResponse();
		
		File &lang = File::Create(sdLangFile);
		lang.Write(response);
		lang.Close();
		delete &lang;
	}
	
	OnProgress("Obtain loaderGX channel.", 0.3);
	if(!File::Exists(Config::WorkingDirectory() + "/LoaderGX.wad"))
	{
		NetworkRequest req("http://www.techjawa.com/usbloadergx/ULNR.file");
		Buffer response = req.GetResponse();
		
		File &wad = File::Create(Config::WorkingDirectory() + "/LoaderGX.wad");
		wad.Write(response);
		wad.Close();
		delete &wad;
	}
	
	OnProgress("Obtain boot.dol", 0.5);
	if(!File::Exists("sd:/apps/usbloader_gx/boot.dol"))
	{
		NetworkRequest req("http://www.techjawa.com/usbloadergx/boot.dol");
		Buffer response = req.GetResponse();
		
		File &boot = File::Create("sd:/apps/usbloader_gx/boot.dol");
		boot.Write(response);
		boot.Close();
		delete &boot;
	}
	
	OnProgress("Obtain readme.txt", 0.6);
	if(!File::Exists("sd:/apps/usbloader_gx/readme.txt"))
	{
		NetworkRequest req("http://docs.google.com/MiscCommands?command=saveasdoc&exportformat=txt&docID=dfwvk5sg_0gksqfcdj");
		Buffer response = req.GetResponse();
		
		File &boot = File::Create("sd:/apps/usbloader_gx/readme.txt");
		boot.Write(response);
		boot.Close();
		delete &boot;
	}
	
	OnProgress("Obtain meta file.", 0.7);
	if(!File::Exists("sd:/apps/usbloader_gx/meta.xml"))
	{
		NetworkRequest req("http://www.techjawa.com/usbloadergx/meta.file");
		Buffer response = req.GetResponse();
		
		File &meta = File::Create("sd:/apps/usbloader_gx/meta.xml");
		meta.Write(response);
		meta.Close();
		delete &meta;
	}
	
	OnProgress("Obtain icon.", 0.8);
	if(!File::Exists("sd:/apps/usbloader_gx/icon.png"))
	{
		NetworkRequest req("http://www.techjawa.com/usbloadergx/icon.png");
		Buffer response = req.GetResponse();
		
		File &icon = File::Create("sd:/apps/usbloader_gx/icon.png");
		icon.Write(response);
		icon.Close();
		delete &icon;
	}
	
	OnProgress("Creating Config.", 0.9);
	if(!File::Exists("sd:/config/GXGlobal.cfg"))
	{		
		File &conf = File::Create("sd:/config/GXGlobal.cfg");
		string confValue = "\nlanguage_path = SD:/config/language/" + _language;
		Buffer confBuffer(confValue.c_str(), confValue.size());
		conf.Write(confBuffer);
		conf.Close();
		delete &conf;
	}
	
	OnProgress("LoaderGX preparation done!", 1);
	return true;
}

void LoaderGX::Install()
{
	Title loader;
	
	OnProgress("Creating LoaderGX channel from wad", 0.1);
	loader.LoadFromWad(Config::WorkingDirectory() + "/LoaderGX.wad");
	
	OnProgress("Installing loaderGX channel", 0.6);
	loader.Install();
	
	OnProgress("LoaderGX installed!", 1);
}
