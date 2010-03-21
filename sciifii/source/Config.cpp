#include "Config.h"
#include "business/common/InstallerFactory.h"
#include "business/common/FileManager.h"
#include <libutils/Xml.h>
#include <libutils/com/NetworkRequest.h>
#include <libutils/system/Title.h>
#include <libutils/fs/File.h>
#include <ogc/conf.h>
#include <cstdlib>
#include <libutils/exception/Exception.h>
#include <libutils/UtilString.h>
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
    catch (...)
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

    if (string(root->Attribute("version")) != SCIIFII_VERSION || string(root->Value()) != "sciifii")
        throw Exception("Config file version not supported", -1);

    c._menuMessage = root->Attribute("MenuMessage");
    c._workingDirectory = root->Attribute("workingDirectory");
    c._useAdvancedSettings = UtilString::ToBool(root->Attribute("AllowAdvancedMode"));

    TiXmlElement* child = root->FirstChildElement();

    if (child == NULL)
        return;

    do
    {
        if (child->Type() != TiXmlElement::COMMENT)
        {
            string nodeValue = UtilString::ToStr(child->Value());

            if (nodeValue == "options")
                c.CreateOptionList(child);
            else if (nodeValue == "modes")
                c.CreateModeList(child);
            else if (nodeValue == "files")
                 FileManager::Init(child);
            else if (nodeValue == "steps")
                c.CreateStepList(child);
            else if (nodeValue == "Disclaimer")
                c._disclaimer = child->FirstChild()->Value();
            else
                throw Exception("Invalid XmlNode.", -1);
        }

        child = child->NextSiblingElement();
    }
    while (child != NULL);

    delete &doc;
}

void Config::CreateOptionList(TiXmlElement* element)
{
    TiXmlElement* child = element->FirstChildElement();

    if (child == NULL)
        return;

    do
    {
        if (child->Type() != TiXmlElement::COMMENT)
        {
            if (string(child->Value()) != "option")
                throw Exception("options child node is invalid", -1);

            string name = child->Attribute("name");
            string text = child->Attribute("text");

            option* opt = new option();
            (*opt) = (option){name, text};
            _options.push_back(opt);
        }

        child = child->NextSiblingElement();
    }
    while (child != NULL);
}

void Config::CreateModeList(TiXmlElement* element)
{
    TiXmlElement* child = element->FirstChildElement();

    if (child == NULL)
        return;

    do
    {
        if (child->Type() != TiXmlElement::COMMENT)
        {
            if (string(child->Value()) != "mode")
                throw Exception("modes child node is invalid", -1);

            string text = child->Attribute("text");
            vector<string> optionList = UtilString::Split(UtilString::ToStr(child->Attribute("options")), '|');
            string flag = child->Attribute("flag");

            mode* m = new mode();
            (*m) = (mode){optionList, text, flag};
            _modes.push_back(m);
        }

        child = child->NextSiblingElement();
    }
    while (child != NULL);
}

void Config::CreateStepList(TiXmlElement* element)
{
    TiXmlElement* child = element->FirstChildElement();

    if (child == NULL)
        return;

    do
    {
        if (child->Type() != TiXmlElement::COMMENT)
        {
            _availableSteps.push_back(InstallerFactory::Create(child));
        }

        child = child->NextSiblingElement();
    }
    while (child != NULL);
}

void Config::ApplyMode(const mode& m)
{
    vector<option*> options = Instance()._options;

    for (vector<option*>::iterator ite = options.begin(); ite != options.end(); ite++)
    {
        bool found = false;
        vector<string> moptions = m.options;
        for (vector<string>::const_iterator site = moptions.begin(); site != moptions.end(); site++)
            if ((*ite)->name == (*site))
            {
                found = true;
                break;
            }

        (*ite)->selected = found;
    }

    if (m.flag != "")
        Instance()._flags.push_back(m.flag);
}

void Config::ValidateOptions()
{
    vector<Installer*> steps = Instance()._availableSteps;
    for (vector<Installer*>::iterator step = steps.begin(); step != steps.end(); step++)
    {
        bool validated = false;

        if ((*step)->Options() == "")
            validated = true;
        else
        {
            vector<string> voptions = UtilString::Split((*step)->Options(), '|');

            for (vector<string>::iterator ite = voptions.begin(); ite != voptions.end(); ite++)
            {
                vector<option*> opts = Instance()._options;
                for (vector<option*>::iterator opt = opts.begin(); opt != opts.end(); opt++)
                {
                    if ((*opt)->name == *ite && (*opt)->selected)
                    {
                        validated = true;
                        break;
                    }
                }
                if (validated)
                    break;
            }
        }

        if (validated)
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

bool Config::IsFlagDefined(const string& flag)
{
	for(vector<string>::iterator ite = Instance()._flags.begin(); ite != Instance()._flags.end(); ite++)
	{
		if(*ite == flag)
			return true;
	}

	return false;
}

u32 Config::GetRegion()
{
  return Instance()._region;
}
