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

	string nodeValue(node->Value());

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
		return CreateSystemUpdater(node);
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
	u32 ciosRevision = Xml::CharToU16(node->Attribute("ciosRevision"));

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



}

void InstallerFactory::FillCiosPatches(Installer* cios, TiXmlElement* xml)
{



}

void InstallerFactory::FillCiosPlugins(Installer* cios, TiXmlElement* xml)
{



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
