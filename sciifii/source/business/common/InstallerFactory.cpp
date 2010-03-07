#include "InstallerFactory.h"
#include "../TitleDowngrader.h"
#include "../IOSReloader.h"
#include "../TruchaRestorer.h"
#include "../TitleInstaller.h"
#include "../CiosCorp.h"
#include "../Cios.h"
#include "../SystemUpdater.h"
#include "../LoaderGX.h"
#include "../WadBatchInstaller.h"
#include "../Preloader.h"
#include <libutils/exception/Exception.h>
#include <libutils/Xml.h>

#include <string>

using namespace std;

Installer* InstallerFactory::Create(TiXmlElement* node)
{
	Installer* step(NULL);

	string nodeValue = Xml::CharToStr(node->Value());

	if(nodeValue == "TitleDowngrader")
	{
		u64 titleId = Xml::CharToU64(node->Attribute("id"),nr_hex);
		u16 revision = Xml::CharToU16(node->Attribute("revision"));
		step = new TitleDowngrader(titleId, revision);
	}
	else if(nodeValue == "IOSReloader")
	{
		u32 id = Xml::CharToU32(node->Attribute("id"));
		UserType ut = (UserType)Xml::CharToU16(node->Attribute("user"));
		step = new IosReloader(id, ut);
	}
	else if(nodeValue == "TruchaRestorer")
	{
		u32 titleId = Xml::CharToU32(node->Attribute("id"));
		u16 revision = Xml::CharToU16(node->Attribute("revision"));
		step = new TruchaRestorer(titleId, revision);
	}
	else if(nodeValue == "TitleInstaller")
	{
		u64 titleId = Xml::CharToU64(node->Attribute("id"), nr_hex);
		u16 revision = Xml::CharToU16(node->Attribute("revision"), nr_hex);
		step = new TitleInstaller(titleId, revision);
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
				string nodeValue = Xml::CharToStr(section->Value());
				if(nodeValue == "items")
					FillCiosCorpItems(step, section);
				else if(nodeValue == "modules")
					FillCiosCorpModules(step, section);
				else
					throw Exception("Child node of Corp not defined>", -1);
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
		string file = Xml::CharToStr(node->Attribute("file"));
		if(file == "")
			throw Exception("Priiloader file must be provided.", -1);

		step = new Preloader(file);
	}
	else if(nodeValue == "WadBatchInstaller")
	{
		string folder = node->Attribute("folder");
		step = new WadBatchInstaller(folder);
	}
	else
		throw Exception("This step doesn't exists", -1);

	step->Options(node->Attribute("option"));

	return step;
}

Installer* InstallerFactory::CreateCios(TiXmlElement* node)
{
	u32 iosSource = Xml::CharToU32(node->Attribute("source"));
	u32 iosDest = Xml::CharToU32(node->Attribute("slot"));

	u16 iosRevision = Xml::CharToU16(node->Attribute("revision"));
	u16 ciosRevision = Xml::CharToU16(node->Attribute("ciosRevision"));

	Cios* step = new Cios(iosSource, iosRevision, iosDest, ciosRevision);

    TiXmlElement* section = node->FirstChildElement();
	while (section != NULL)
	{
		if (section->Type() != TiXmlElement::COMMENT)
		{
			string nodeValue = Xml::CharToStr(section->Value());
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
			if(Xml::CharToStr(module->Value()) != "module")
				throw Exception("There can only be module item in modules", -1);
				
			string name = Xml::CharToStr(module->Attribute("file"));
            s32 position = Xml::CharToS32(module->Attribute("position"), -1);
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
           string nodeValue = Xml::CharToStr(child->Value());
           if(nodeValue=="prebuild")
           {
               string patchName=Xml::CharToStr(child->Attribute("name"));
               ((Cios*)cios)->AddPatch(SimplePatch::getPatch(patchName));
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
			if(Xml::CharToStr(plugin->Value()) != "plugin")
				throw Exception("There can only be plugin item in plugins", -1);

			string dest = Xml::CharToStr(plugin->Attribute("dest"));
			string file = Xml::CharToStr(plugin->Attribute("file"));
			u32 offset = Xml::CharToU32(plugin->Attribute("offset"), nr_hex);
			u32 bss = Xml::CharToU32(plugin->Attribute("bss"), nr_hex);
			vector<SimplePatch> handles = GetPluginHandles(plugin);
			((Cios*)cios)->AddPlugin((pluginDescriptor){ dest, file, offset, bss, handles });
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
			if(Xml::CharToStr(handle->Value()) != "handle")
				throw Exception("There can only be handle item in plugin", -1);

            Buffer pattern;
            Buffer value;
            vector<string> splitPattern = Config::SplitString(Xml::CharToStr(handle->Attribute("pattern")),',');
            vector<string> splitValue = Config::SplitString(Xml::CharToStr(handle->Attribute("value")),',');
			
            for(u16 i = 0; i < splitPattern.size(); i++)
            {
               vector<string> val = Config::SplitString(splitPattern[i], 'x');
               if(val.size() != 2)
                    throw Exception("Value length !=2",-1);

               u8 v = (u8)Xml::CharToU16(val[1].c_str());
               pattern.Append(&v, 1);
            }
			
            for(u16 i = 0; i < splitValue.size(); i++)
            {
               vector<string> val = Config::SplitString(splitValue[i], 'x');
               u8 v = (u8)Xml::CharToU16(val[1].c_str());
               value.Append(&v, 1);
            }
			
			patches.push_back(SimplePatch((u8*)pattern.Content(),(u8*)value.Content(),pattern.Length()));
		}
		handle = handle->NextSiblingElement();
	}

	return patches;
}

void InstallerFactory::FillCiosCorpItems(Installer* corp, TiXmlElement* xml)
{
	TiXmlElement* child = xml->FirstChildElement();
    while (child != NULL)
    {
        if (child->Type() != TiXmlElement::COMMENT)
        {
            if (string(child->Value()) != "corpItem")
                throw Exception("CorpItem child node is invalid", -1);

            u64 slot = Xml::CharToU64(child->Attribute("slot"),nr_hex);
            u64 source = Xml::CharToU64(child->Attribute("source"),nr_hex);
            u16 revision = Xml::CharToU16(child->Attribute("revision"));
            vector<string> modules = Config::SplitString(Xml::CharToStr(child->Attribute("modules")), '|');
            bool identifyPatch = Xml::CharToBool(child->Attribute("identifyPatch"));
            bool nandPatch = Xml::CharToBool(child->Attribute("nandPatch"));
            bool kkPatch = Xml::CharToBool(child->Attribute("kkPatch"));
            bool localOnly = Xml::CharToBool(child->Attribute("localOnly"));

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
            if (string(child->Value()) != "module")
                throw Exception("CorpItem module child node is invalid", -1);

            string type = Xml::CharToStr(child->Attribute("type"));
			string name = Xml::CharToStr(child->Attribute("name"));
			string file = Xml::CharToStr(child->Attribute("file"));

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
            if (string(child->Value()) != "title")
                throw Exception("UpdateList child node is invalid", -1);

            u64 id = Xml::CharToU64(child->Attribute("id"), nr_hex);
            u16 revision = Xml::CharToU16(child->Attribute("revision"));
            bool onlyUninstallation = Xml::CharToBool(child->Attribute("onlyUninstallation"));
            s8 region = Xml::CharToS32(child->Attribute("region"));
			u64 slot = Xml::CharToU64(child->Attribute("slot"), 0);

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
