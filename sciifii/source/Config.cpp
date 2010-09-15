#include "Config.h"
#include "business/common/InstallerFactory.h"
#include "business/common/FileManager.h"
#include <libwiisys.h>
#include <ogc/conf.h>
#include <cstdlib>

using namespace std;
using namespace Libwiisys;
using namespace Libwiisys::Network;
using namespace Libwiisys::Logging;
using namespace Libwiisys::Serialization;
using namespace Libwiisys::String;
using namespace Libwiisys::Exceptions;
Config::Config()
        : _hasNetwork(false),
        _uninstall(false)
{
    try
    {
        _region = CONF_GetRegion();
        NetworkUtility::GetIp();
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
    
    if(Config::HasNetwork())
    {
      WebLogger *sciifiiLog=new WebLogger("http://www.teamwiigen.fr.cr/WebLogging/Logger.aspx", "message", "line", "file", "application", "version");
      Log::AddLogProvider(Lgt_All, sciifiiLog);
    }
    
    TiXmlDocument& doc = Xml::Load("sd:/sciifii/config.xml");
    TiXmlElement* root = doc.RootElement();

    if (string(root->Attribute("version")) != SCIIFII_VERSION || string(root->Value()) != "sciifii")
        throw Exception("Config file version not supported", -1);

    c._menuMessage = root->Attribute("MenuMessage");
    c._workingDirectory = UtilString::ToStr(root->Attribute("workingDirectory"), "sd:/sciifii/temp/");;
    c._useAdvancedSettings = UtilString::ToBool(root->Attribute("AllowAdvancedMode"), true);
    
    TiXmlElement* child = root->FirstChildElement();

    while (child != NULL)
    {
        if (child->Type() != TiXmlElement::COMMENT)
        {
            string nodeValue = UtilString::ToStr(child->Value());

            if (nodeValue == "options")
                c.CreateOptionList(child);
            else if(nodeValue=="logs")
            	c.CreateLogs(child);
            else if (nodeValue == "modes")
                c.CreateModeList(child);
            else if (nodeValue == "files")
                 FileManager::Init(child);
            else if (nodeValue == "steps")
                c.CreateStepList(child);
            else if (nodeValue == "Disclaimer")
                c._disclaimer = UtilString::Replace(UtilString::ToStr(child->FirstChild()->Value(), ""), "\\n", "\n");
            else
                throw Exception("Invalid XmlNode.", -1);
        }

        child = child->NextSiblingElement();
    }


    delete &doc;
}

void Config::CreateLogs(TiXmlElement* element)
{
  TiXmlElement* child = element->FirstChildElement();

  while (child != NULL)
  {
    if (child->Type() != TiXmlElement::COMMENT)
    {
      if (string(child->Value()) != "log")
        throw Exception("options child node is invalid", -1);

      string type = UtilString::ToStr(child->Attribute("type"));
      string cat = UtilString::ToStr(child->Attribute("category"),"all");
      string path =UtilString::ToStr(child->Attribute("path"),"");
      string url =UtilString::ToStr(child->Attribute("url"),"");
      LogType t;
      if(cat=="error")
        t = Lgt_Error;
      else if (cat == "warning")
        t = Lgt_Warning;
      else if (cat == "info")
        t = Lgt_Info;
      else if (cat == "all")
        t = Lgt_All;
      else
        throw Exception("Invalid log category : "+cat, -1);

      if(type=="file")
      {
        if(path=="" )
          throw Exception("File logger needs a file path !", -1);

          FileLogger* l = new FileLogger(path);
          Log::AddLogProvider(t,l);
      }
      else if (type=="gecko")
      {
        GeckoLogger* g = new GeckoLogger();
        Log::AddLogProvider(t,g);
      }
      else if (type=="web")
      {
    	  if(url=="")
    		  throw Exception("Weblogger needs an url for logging  !", -1);
    	  WebLogger *sciifiiLog=new WebLogger(url, "message", "line", "file", "application", "version");
    	  Log::AddLogProvider(t, sciifiiLog);
      }
      else
        throw Exception("Invalid log type : " + type, -1);
    }

    child = child->NextSiblingElement();
  }
}

void Config::CreateOptionList(TiXmlElement* element)
{
    TiXmlElement* child = element->FirstChildElement();

    while (child != NULL)
    {
        if (child->Type() != TiXmlElement::COMMENT)
        {
            if (string(child->Value()) != "option")
                throw Exception("options child node is invalid", -1);

            string name = child->Attribute("name");
            string text = child->Attribute("text");
            bool hidden = UtilString::ToBool(child->Attribute("hidden"),false);
            vector<string> regions = UtilString::Split(UtilString::ToStr(child->Attribute("regions"), ""), ',', true);
            
            bool valid = regions.size() == 0;

			for(vector<string>::iterator ite = regions.begin(); ite != regions.end(); ite++)
			{
			  if(UtilString::ToU32(ite->c_str()) == GetRegion())
			  {
				valid = true;
				break;
			  }
			}

            if(valid)
            {
            	option* opt = new option();
				(*opt) = (option){name, text,false,hidden};
				_options.push_back(opt);
            }
        }

        child = child->NextSiblingElement();
    }

}

void Config::CreateModeList(TiXmlElement* element)
{
    TiXmlElement* child = element->FirstChildElement();

    while (child != NULL)
    {
        if (child->Type() != TiXmlElement::COMMENT)
        {
            if (string(child->Value()) != "mode")
                throw Exception("modes child node is invalid", -1);

            string text = child->Attribute("text");
            vector<string> optionList = UtilString::Split(UtilString::ToStr(child->Attribute("options")), '|');
            vector<string> regions = UtilString::Split(UtilString::ToStr(child->Attribute("regions"), ""), ',', true);

            bool valid = regions.size() == 0;

			for(vector<string>::iterator ite = regions.begin(); ite != regions.end(); ite++)
			{
			  s8 region;
			  stringstream sregion(*ite);
			  sregion >> region;
			  if(region == -1 || (u32)region == GetRegion())
			  {
				valid = true;
				break;
			  }
			}
            
            if(valid)
            {
            	mode* m = new mode();
				(*m) = (mode){optionList, text};
				_modes.push_back(m);
            }
        }

        child = child->NextSiblingElement();
    }
}

void Config::CreateStepList(TiXmlElement* element)
{
    TiXmlElement* child = element->FirstChildElement();


    while (child != NULL)
    {
        if (child->Type() != TiXmlElement::COMMENT)
        {
          Installer* step = InstallerFactory::Create(child);
          bool addToList = step->Region().size() == 0;
          
          for(vector<u32>::iterator ite = step->Region().begin(); ite != step->Region().end(); ite++)
            if(*ite == GetRegion())
            {
              addToList = true;
              break;
            }
          
          if(addToList)
            _availableSteps.push_back(step);
          else
            delete step;
        }

        child = child->NextSiblingElement();
    }

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
}

void Config::ValidateOptions()
{
	cout << "\x1b[2J";
	cout << "\x1b[2;0H";
	cout << "Sciifii is analysing your choice" << endl;
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
                {
                	cout<<".";
                    break;
                }
            }
        }

        if (validated)
        {
            Instance()._validatedSteps.push_back(*step);
            (*step)->SendToLog();
        }
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

u32 Config::GetRegion()
{
  return Instance()._region;
}
