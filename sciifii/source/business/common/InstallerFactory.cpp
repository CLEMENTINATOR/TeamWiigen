#include "InstallerFactory.h"
#include "../TitleDowngrader.h"
#include "../IOSReloader.h"
#include "../TitleStep.h"
#include "../CiosCorp.h"
#include "../Cios.h"
#include "../SystemUpdater.h"
#include "../LoaderGX.h"
#include "../WadBatchInstaller.h"
#include "../Preloader.h"
#include "../CompositeInstaller.h"
#include "../FileDownloader.h"
#include "../FileSystemTask.h"
#include <libutils/exception/Exception.h>
#include <libutils/Xml.h>
#include <libutils/UtilString.h>
#include <libutils/system/Title.h>

#include <string>

using namespace std;

Installer* InstallerFactory::Create(TiXmlElement* node)
{
	Installer* step(NULL);

	string nodeValue = UtilString::ToStr(node->Value());

	if(nodeValue == "TitleDowngrader")
	{
		u64 titleId = UtilString::ToU64(node->Attribute("id"),nr_hex);
		u16 revision = UtilString::ToU16(node->Attribute("revision"));
		step = new TitleDowngrader(titleId, revision);
	}
	else if(nodeValue == "IOSReloader")
	{
		u32 id = UtilString::ToU32(node->Attribute("id"));
		s32 userId = UtilString::ToS32(node->Attribute("user"), -1);
		if(userId == -1)
			step = new IosReloader(id);
		else
		{
			u16 realUserId = (u16)userId;
			UserType ut = (UserType)realUserId;
			step = new IosReloader(id, ut);
		}
	}
	else if(nodeValue == "Title")
	{
		u64 titleId = UtilString::ToU64(node->Attribute("id"),0, nr_hex);
		u16 revision = UtilString::ToU16(node->Attribute("revision"),0, nr_hex);
        string file = UtilString::ToStr(node->Attribute("wad"),"");
        string path = UtilString::ToStr(node->Attribute("path"),"");
        TitleAction action;
        string choice = UtilString::ToStr(node->Attribute("action"),"Install");

		if(choice == "Install")
			action = ti_Install;
		else if(choice == "Uninstall")
			action = ti_Uninstall;
		else if (choice == "Pack")
		    action = ti_PackAsWad;
		else if (choice == "Extract")
		    action = ti_Extract;
        else if (choice=="Decrypt")
            action = ti_Decrypt;
        else
			throw Exception("Can't parse WadAction enum from xml!", -1);

         if (titleId!=0 && file=="")
        {
            step= new TitleStep(titleId, revision, action, path);
        }
         else if (titleId==0 && file!="")
        {
            step= new TitleStep(file, action, path);
        }
        else  throw Exception("Title XML error", -1);
	}
	else if(nodeValue == "CiosInstaller")
	{
		step = CreateCios(node);
	}
	else if(nodeValue == "CorpInstaller")
	{
		step = new CiosCorp();

		TiXmlElement* section = node->FirstChildElement();
		while (section != NULL)
		{
			if (section->Type() != TiXmlElement::COMMENT)
			{
				string nodeValue = UtilString::ToStr(section->Value());
				if(nodeValue == "items")
					FillCiosCorpItems(step, section);
				else if(nodeValue == "modules")
					FillCiosCorpModules(step, section);
				else
					throw Exception("Child node of Corp not defined.", -1);
			}
			section=section->NextSiblingElement();
		}
	}
	else if(nodeValue == "SystemUpdater")
	{
		step = CreateSystemUpdater(node);
	}
	else if(nodeValue == "GXLoader")
	{
		step = new LoaderGX();
	}
	else if(nodeValue == "Preloader")
	{
		string file = UtilString::ToStr(node->Attribute("file"));
		if(file == "")
			throw Exception("Priiloader file must be provided.", -1);

		step = new Preloader(file);
	}
	else if(nodeValue == "WadBatchInstaller")
	{
		string folder = UtilString::ToStr(node->Attribute("folder"));
		step = new WadBatchInstaller(folder);
	}
	else if(nodeValue == "CompositeInstaller")
	{
		string name = UtilString::ToStr(node->Attribute("name"));
		step = new CompositeInstaller(name);
		FillCompositeInstaller(step, node);
	}
	else if(nodeValue == "FileDownloader")
	{
		string file = UtilString::ToStr(node->Attribute("file"));
		step = new FileDownloader(file);
	}
	else if(nodeValue == "FileSystem")
	{
		string target = UtilString::ToStr(node->Attribute("target"));
		string destination = UtilString::ToStr(node->Attribute("destination"), "");
		string saction = UtilString::ToStr(node->Attribute("action"));
		string stype = UtilString::ToStr(node->Attribute("type"));
		bool recursive = UtilString::ToBool(node->Attribute("recursive"), false);

		FSTType type = FSTType_File;
		FSTAction action = FSTAction_Move;

		if(stype == "file")
			;
		else if(stype == "folder")
			type = FSTType_Folder;
		else
			throw Exception("Can't parse FSTType from \"" + stype + "\".", -1);

		if(saction == "move")
			;
		else if(saction == "copy")
			action = FSTAction_Copy;
		else if(saction == "delete")
			action = FSTAction_Delete;

		return new FileSystemTask(target, action, type, destination, recursive);
	}
	else
		throw Exception("This step doesn't exists", -1);

	step->Options(UtilString::ToStr(node->Attribute("option"), ""));

	return step;
}

Installer* InstallerFactory::CreateCios(TiXmlElement* node)
{
	u32 iosSource = UtilString::ToU32(node->Attribute("source"));
	u32 iosDest = UtilString::ToU32(node->Attribute("slot"));

	u16 iosRevision = UtilString::ToU16(node->Attribute("revision"));
	u16 ciosRevision = UtilString::ToU16(node->Attribute("ciosRevision"));

	Cios* step = new Cios(iosSource, iosRevision, iosDest, ciosRevision);

    TiXmlElement* section = node->FirstChildElement();
	while (section != NULL)
	{
		if (section->Type() != TiXmlElement::COMMENT)
		{
			string nodeValue = UtilString::ToStr(section->Value());
			if(nodeValue == "modules")
			   FillCiosModules(step, section);
			else if(nodeValue == "plugins")
				FillCiosPlugins(step, section);
			else if(nodeValue=="patches")
				FillCiosPatches(step, section);
			else
				throw Exception("Child node of Cios not defined", -1);
		}
		section=section->NextSiblingElement();
	}

	return step;
}


void InstallerFactory::FillCiosModules(Installer* cios, TiXmlElement* xml)
{
    TiXmlElement* module = xml->FirstChildElement();
    while (module != NULL)
    {
        if (module->Type() != TiXmlElement::COMMENT)
        {
			if(UtilString::ToStr(module->Value()) != "module")
				throw Exception("There can only be module item in modules", -1);

			string name = UtilString::ToStr(module->Attribute("file"));
            s32 position = UtilString::ToS32(module->Attribute("position"), -1);
            ((Cios*)cios)->AddModule((customModule){name, position});
        }
        module = module->NextSiblingElement();
    }
}

void InstallerFactory::FillCiosPatches(Installer* cios, TiXmlElement* xml)
{
    TiXmlElement* child = xml->FirstChildElement();
    while (child != NULL)
    {
        if (child->Type() != TiXmlElement::COMMENT)
        {
           string nodeValue = UtilString::ToStr(child->Value());
           if(nodeValue=="prebuild")
           {
               string patchName=UtilString::ToStr(child->Attribute("name"));
               ((Cios*)cios)->AddPatch(SimplePatch::getPatch(patchName));
           }
            if(nodeValue=="SimplePatch")
           {
            string module=UtilString::ToStr(child->Attribute("module"),"");
            Buffer pattern;
            Buffer value;
            vector<string> splitPattern = UtilString::Split(UtilString::ToStr(child->Attribute("pattern")),',');
            vector<string> splitValue = UtilString::Split(UtilString::ToStr(child->Attribute("value")),',');

            for(u16 i = 0; i < splitPattern.size(); i++)
            {
               vector<string> val = UtilString::Split(splitPattern[i], 'x');
               if(val.size() != 2)
                    throw Exception("Value length !=2",-1);

               u8 v = UtilString::ToU8(val[1].c_str(), nr_hex);
               pattern.Append(&v, 1);
            }

            for(u16 i = 0; i < splitValue.size(); i++)
            {
               vector<string> val = UtilString::Split(splitValue[i], 'x');
               u8 v = UtilString::ToU8(val[1].c_str(), nr_hex);
               value.Append(&v, 1);
            }
            SimplePatch*s=new SimplePatch((u8*)pattern.Content(),(u8*)value.Content(),pattern.Length(),module);
                ((Cios*)cios)->AddPatch(s);
           }

        }
        child = child->NextSiblingElement();
    }
}

void InstallerFactory::FillCiosPlugins(Installer* cios, TiXmlElement* xml)
{
	TiXmlElement* plugin = xml->FirstChildElement();
	while (plugin != NULL)
	{
		if (plugin->Type() != TiXmlElement::COMMENT)
		{
			if(UtilString::ToStr(plugin->Value()) != "plugin")
				throw Exception("There can only be plugin item in plugins", -1);

			string dest = UtilString::ToStr(plugin->Attribute("dest"));
			string file = UtilString::ToStr(plugin->Attribute("file"));
			u32 offset = UtilString::ToU32(plugin->Attribute("offset"),0, nr_hex);
			u32 bss = UtilString::ToU32(plugin->Attribute("bss"),0, nr_hex);
			u32 segment = UtilString::ToU32(plugin->Attribute("segment"),0);
			vector<SimplePatch> handles = GetPluginHandles(plugin);

			//get headers
			Elf32_Phdr header;
			bool hasHeader = GetPluginHeader(plugin, header);
			((Cios*)cios)->AddPlugin((pluginDescriptor){ dest, file, offset, bss, handles, hasHeader, segment, header });
		}
		 plugin = plugin->NextSiblingElement();
	}
}

vector<SimplePatch> InstallerFactory::GetPluginHandles(TiXmlElement* xml)
{
	vector<SimplePatch> patches;
	TiXmlElement* handle = xml->FirstChildElement();

	while (handle != NULL)
	{
		if (handle->Type() != TiXmlElement::COMMENT)
		{
			if(UtilString::ToStr(handle->Value()) == "handle")
			{
				Buffer pattern;
				Buffer value;
				vector<string> splitPattern = UtilString::Split(UtilString::ToStr(handle->Attribute("pattern")),',');
				vector<string> splitValue = UtilString::Split(UtilString::ToStr(handle->Attribute("value")),',');

				for(u16 i = 0; i < splitPattern.size(); i++)
				{
				   vector<string> val = UtilString::Split(splitPattern[i], 'x');
				   if(val.size() != 2)
						throw Exception("Value length !=2",-1);

				   u8 v = UtilString::ToU8(val[1].c_str(), nr_hex);
				   pattern.Append(&v, 1);
				}

				for(u16 i = 0; i < splitValue.size(); i++)
				{
				   vector<string> val = UtilString::Split(splitValue[i], 'x');
				   u8 v = UtilString::ToU8(val[1].c_str(), nr_hex);
				   value.Append(&v, 1);
				}

				patches.push_back(SimplePatch((u8*)pattern.Content(),(u8*)value.Content(),pattern.Length()));
			}
		}
		handle = handle->NextSiblingElement();
	}

	return patches;
}

bool InstallerFactory::GetPluginHeader(TiXmlElement* xml, Elf32_Phdr& header)
{
	TiXmlElement* handle = xml->FirstChildElement();

	while (handle != NULL)
	{
		if (handle->Type() != TiXmlElement::COMMENT)
		{
			if(UtilString::ToStr(handle->Value()) == "header")
			{
				header.p_type = UtilString::ToU32(handle->Attribute("type"));
				header.p_vaddr = UtilString::ToU32(handle->Attribute("vaddr"), nr_hex);
				header.p_paddr = UtilString::ToU32(handle->Attribute("paddr"), nr_hex);
				header.p_flags = UtilString::ToU32(handle->Attribute("flag"), nr_hex);
				header.p_align = UtilString::ToU32(handle->Attribute("align"));
				return true;
			}
		}
		handle = handle->NextSiblingElement();
	}

	return false;
}

void InstallerFactory::FillCiosCorpItems(Installer* corp, TiXmlElement* xml)
{
	TiXmlElement* child = xml->FirstChildElement();
    while (child != NULL)
    {
        if (child->Type() != TiXmlElement::COMMENT)
        {
            if (UtilString::ToStr(child->Value()) != "corpItem")
                throw Exception("CorpItem child node is invalid", -1);

            u64 slot = UtilString::ToU64(child->Attribute("slot"),nr_hex);
            u64 source = UtilString::ToU64(child->Attribute("source"),nr_hex);
            u16 revision = UtilString::ToU16(child->Attribute("revision"));
            vector<string> modules = UtilString::Split(UtilString::ToStr(child->Attribute("modules")), '|');
            bool identifyPatch = UtilString::ToBool(child->Attribute("identifyPatch"));
            bool nandPatch = UtilString::ToBool(child->Attribute("nandPatch"));
            bool kkPatch = UtilString::ToBool(child->Attribute("kkPatch"));
            bool localOnly = UtilString::ToBool(child->Attribute("localOnly"));

			((CiosCorp*)corp)->AddItem((ciosDesc){ slot, source, revision, modules, identifyPatch, nandPatch, kkPatch, localOnly });
        }

        child = child->NextSiblingElement();
    }
}

void InstallerFactory::FillCiosCorpModules(Installer* corp, TiXmlElement* xml)
{
	TiXmlElement* child = xml->FirstChildElement();
    while (child != NULL)
    {
        if (child->Type() != TiXmlElement::COMMENT)
        {
            if (UtilString::ToStr(child->Value()) != "module")
                throw Exception("CorpItem module child node is invalid", -1);

            string type = UtilString::ToStr(child->Attribute("type"));
			string name = UtilString::ToStr(child->Attribute("name"));
			string file = UtilString::ToStr(child->Attribute("file"));

			((CiosCorp*)corp)->AddModule(name, (moduleDesc){ type, file });
        }

        child = child->NextSiblingElement();
    }
}

Installer* InstallerFactory::CreateSystemUpdater(TiXmlElement* node)
{
	SystemUpdater* step = new SystemUpdater();
	TiXmlElement* child = node->FirstChildElement();

    while(child != NULL)
    {
        if (child->Type() != TiXmlElement::COMMENT)
        {
            if (UtilString::ToStr(child->Value()) != "title")
                throw Exception("UpdateList child node is invalid", -1);

            u64 id = UtilString::ToU64(child->Attribute("id"), nr_hex);
            u16 revision = UtilString::ToU16(child->Attribute("revision"));
            bool onlyUninstallation = UtilString::ToBool(child->Attribute("onlyUninstallation"));
            s8 region = UtilString::ToS32(child->Attribute("region"), -1);
			u64 slot = UtilString::ToU64(child->Attribute("slot"), 0);

            if (region == -1 || region == (s32)Config::GetRegion())
            {
				titleDescriptor descriptor = (titleDescriptor){slot, id, revision};

				u32 type = id >> 32;
				//skip some channels
				if (type != 1 && Title::IsInstalled(id))
					if (Title::GetInstalledTitleVersion(id) >= revision)
					{
						child = child->NextSiblingElement();
						continue;
					}

				step->AddTitle(descriptor, onlyUninstallation);
            }
        }

        child = child->NextSiblingElement();
    };

	return step;
}

void InstallerFactory::FillCompositeInstaller(Installer* composite, TiXmlElement* node)
{
	CompositeInstaller* step = (CompositeInstaller*)composite;

	TiXmlElement* child = node->FirstChildElement();

    while(child != NULL)
    {
        if (child->Type() != TiXmlElement::COMMENT)
        {
            step->AddStep(InstallerFactory::Create(child));
        }

        child = child->NextSiblingElement();
    };
}
