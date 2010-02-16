#include "Config.h"
#include "business/common/InstallerFactory.h"
#include <libutils/Xml.h>
#include <libutils/com/NetworkRequest.h>
#include <libutils/system/Title.h>
#include <ogc/conf.h>
#include <cstdlib>
#include <libutils/exception/Exception.h>
#include <ogc/conf.h>
using namespace std;

Config::Config()
: _hasNetwork(false),
  _uninstall(false)
{
	try
	{
		_region = CONF_GetRegion();
		NetworkRequest::GetIp();
		_hasNetwork = true;
	}
	catch(...)
	{}
}

bool Config::HasNetwork()
{
	return Instance()._hasNetwork;
}

string Config::WorkingDirectory()
{
	return Instance()._workingDirectory;
}

vector<ciosDesc> Config::CorpConfiguration()
{
	return Instance()._corp;
}

Config& Config::Instance()
{
	static Config c;
	return c;
}

void Config::Initialize()
{
	Config& c = Instance();
	TiXmlDocument& doc = Xml::Load("sd:/sciifii/config.xml");
	TiXmlElement* root = doc.RootElement();

	if(string(root->Attribute("version")) != SCIIFII_VERSION || string(root->Value()) != "sciifii")
		throw Exception("Config file version not supprted", -1);

	c._menuMessage = root->Attribute("MenuMessage");
	c._workingDirectory = root->Attribute("workingDirectory");
	c._useAdvancedSettings = Xml::StrToBool(root->Attribute("AllowAdvancedMode"));

	TiXmlElement* child = root->FirstChildElement();

	if(child == NULL)
		return;

	do
	{
		if(child->Type() != TiXmlElement::COMMENT)
		{
			string nodeValue(child->Value());

			if(nodeValue == "corp")
				c.CreateCorpList(child);
			else if(nodeValue == "system")
				c.CreateUpdateList(child);
			else if(nodeValue == "options")
				c.CreateOptionList(child);
			else if(nodeValue == "modes")
				c.CreateModeList(child);
			else if(nodeValue == "steps")
				c.CreateStepList(child);
			else
				throw Exception("Invalid XmlNode.", -1);
		}

		child = child->NextSiblingElement();
	} while(child != NULL);

}

void Config::CreateCorpList(TiXmlElement* element)
{
	TiXmlElement* child = element->FirstChildElement();

	if(child == NULL)
		return;

	do
	{
		if(child->Type() != TiXmlElement::COMMENT)
		{
			if(string(child->Value()) != "corpItem")
				throw Exception("CorpItem child node is invalid", -1);

			u32 slot = Xml::StrToU32(child->Attribute("slot"));
			u32 source = Xml::StrToU32(child->Attribute("source"));
			u16 revision = Xml::StrToU16(child->Attribute("revision"));
			u8 dipVersion = Xml::StrToU8(child->Attribute("dipVersion"));
			u8 esVersion = Xml::StrToU8(child->Attribute("esVersion"));
			bool identifyPatch = Xml::StrToBool(child->Attribute("identifyPatch"));
			bool nandPatch = Xml::StrToBool(child->Attribute("nandPatch"));
			bool kkPatch = Xml::StrToBool(child->Attribute("kkPatch"));
			bool localOnly = Xml::StrToBool(child->Attribute("localOnly"));

			_corp.push_back((ciosDesc) { slot, source, revision, dipVersion, esVersion, identifyPatch, nandPatch, kkPatch, localOnly});
		}

		child = child->NextSiblingElement();
	} while(child != NULL);
}

void Config::CreateUpdateList(TiXmlElement* element)
{
	TiXmlElement* child = element->FirstChildElement();

	if(child == NULL)
		return;

	do
	{
		if(child->Type() != TiXmlElement::COMMENT)
		{
			if(string(child->Value()) != "title")
				throw Exception("UpdateList child node is invalid", -1);

			u64 id = Xml::StrToU64(child->Attribute("id"));
			u16 revision= Xml::StrToU16(child->Attribute("revision"));
			bool onlyUninstallation= Xml::StrToBool(child->Attribute("onlyUninstallation"));
			s8 region = Xml::StrToS32(child->Attribute("region"));

			if(region == -1 || region == _region)
			{
				_systemTitleList.push_back((titleDescriptor){ id, revision, onlyUninstallation});
				if(!onlyUninstallation)
					_updateList.push_back((titleDescriptor){ id, revision, onlyUninstallation});
			}
		}

		child = child->NextSiblingElement();
	} while(child != NULL);
}

void Config::CreateOptionList(TiXmlElement* element)
{
	TiXmlElement* child = element->FirstChildElement();

	if(child == NULL)
		return;

	do
	{
		if(child->Type() != TiXmlElement::COMMENT)
		{
			if(string(child->Value()) != "option")
				throw Exception("options child node is invalid", -1);

			string name = child->Attribute("name");
			string text = child->Attribute("text");

			option* opt = new option();
			(*opt) = (option) { name, text};
			_options.push_back(opt);
		}

		child = child->NextSiblingElement();
	} while(child != NULL);
}

void Config::CreateModeList(TiXmlElement* element)
{
	TiXmlElement* child = element->FirstChildElement();

	if(child == NULL)
		return;

	do
	{
		if(child->Type() != TiXmlElement::COMMENT)
		{
			if(string(child->Value()) != "mode")
					throw Exception("modes child node is invalid", -1);

			string text = child->Attribute("text");
			vector<string> optionList = GetOptionList(child->Attribute("options"));
			string flag = child->Attribute("flag");

			mode* m = new mode();
			(*m) = (mode){ optionList, text, flag};
			_modes.push_back(m);
		}

		child = child->NextSiblingElement();
	} while(child != NULL);
}

void Config::CreateStepList(TiXmlElement* element)
{
	TiXmlElement* child = element->FirstChildElement();

	if(child == NULL)
		return;

	do
	{
		if(child->Type() != TiXmlElement::COMMENT)
		{
			_availableSteps.push_back(InstallerFactory::Create(child));
		}

		child = child->NextSiblingElement();
	} while(child != NULL);
}

vector<string> Config::GetOptionList(const std::string& options)
{
	vector<string> voptions;
	string modeOptions = options;
	u32 position = 0;

	while((position = modeOptions.find_first_of("|")) != string::npos)
	{
		voptions.push_back(modeOptions.substr(0, position));
		modeOptions = modeOptions.erase(0, position + 1);
	}

	voptions.push_back(modeOptions);

	return voptions;
}

void Config::ApplyMode(const mode& m)
{
	for(vector<option*>::iterator ite = Instance()._options.begin(); ite != Instance()._options.end(); ite++)
	{
		bool found = false;
		for(vector<string>::const_iterator site = m.options.begin(); site != m.options.end(); site++)
			if((*ite)->name == (*site))
			{
				found = true;
				break;
			}

		(*ite)->selected = found;
	}

	if(m.flag == "Uninstall")
		Instance()._uninstall = true;
}

void Config::ValidateOptions()
{
	for(vector<Installer*>::iterator step = Instance()._availableSteps.begin(); step != Instance()._availableSteps.end(); step++)
	{
		bool validated = false;
		vector<string> voptions = GetOptionList((*step)->Options());

		for(vector<string>::iterator ite = voptions.begin(); ite != voptions.end(); ite++)
		{
			for(vector<option*>::iterator opt = Instance()._options.begin(); opt != Instance()._options.end(); opt++)
			{
				if((*opt)->name == *ite)
				{
					validated = true;
					break;
				}
			}
			if(validated)
				break;
		}

		if(validated)
			Instance()._validatedSteps.push_back(*step);
	}
}

vector<mode*> Config::Modes()
{
	return Instance()._modes;
}

vector<option*> Config::Options()
{
	return Instance()._options;
}

vector<Installer*> Config::Steps()
{
	return Instance()._validatedSteps;
}

string Config::MenuMessage()
{
	return Instance()._menuMessage;
}

string Config::DisclaimerText()
{
	return Instance()._disclaimer;
}

bool Config::UseAdvancedMode()
{
	return Instance()._useAdvancedSettings;
}

vector<titleDescriptor> Config::UpdateConfiguration()
{
	if(Instance()._uninstall)
		return Instance()._systemTitleList;
	else
		return Instance()._updateList;
}
