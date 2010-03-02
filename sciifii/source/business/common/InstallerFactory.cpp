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
	}
	else if(nodeValue == "SystemUpdater")
	{
		step = new SystemUpdater();
	}
	else if(nodeValue == "GXLoader")
	{
		step = new LoaderGX();
	}
	else if(nodeValue == "Preloader")
	{
		string url = Xml::CharToStr(node->Attribute("url"));
		string sha = Xml::CharToStr(node->Attribute("sha"));
		step = new Preloader(url, sha);
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
	
	Installer* step = new Cios(iosSource, iosRevision, iosDest, ciosRevision);
	
	return step;
}