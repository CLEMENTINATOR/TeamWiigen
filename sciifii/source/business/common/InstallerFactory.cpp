#include "InstallerFactory.h"
#include "../IOSDowngrader.h"
#include "../IOSReloader.h"
#include "../TruchaRestorer.h"
#include "../TitleInstaller.h"
#include "../Cios.h"
#include "../CiosCorp.h"
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

		if(nodeValue == "IOSDowngrader")
		{
			u32 titleId = Xml::StrToU32(node->Attribute("id"));
			u16 revision = Xml::StrToU16(node->Attribute("revision"));
			step = new IosDowngrader(titleId, revision);
		}
		else if(nodeValue == "IOSReloader")
		{
			u32 id = Xml::StrToU32(node->Attribute("id"));
			UserType ut = (UserType)Xml::StrToU16(node->Attribute("user"));
			string fs = node->Attribute("fs");
			if(fs.size() > 0)
				fs = fs + ":/";

			step = new IosReloader(id, ut, fs);
		}
		else if(nodeValue == "TruchaRestorer")
		{
			u32 titleId = Xml::StrToU32(node->Attribute("id"));
			u16 revision = Xml::StrToU16(node->Attribute("revision"));
			step = new TruchaRestorer(titleId, revision);
		}
		else if(nodeValue == "TitleInstaller")
		{
			u32 titleId = Xml::StrToU32(node->Attribute("id"));
			u16 revision = Xml::StrToU16(node->Attribute("revision"));
			step = new TitleInstaller(titleId, revision);
		}
		else if(nodeValue == "CiosInstaller")
		{
			step = new Cios();
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
			step = new Preloader();
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
