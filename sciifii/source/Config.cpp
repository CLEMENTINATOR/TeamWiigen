#include <ogc/conf.h>
#include <cstdlib>
#include <iostream>

#include <sciifii/Config.h>
#include <sciifii/business/common/FileManager.h>
#include <sciifii/business/common/InstallerFactory.h>
#include <sciifii/ui/text/MenuManager.h>
#include <sciifii/ui/graphic/GMenuManager.h>
#include <Libwiisys/Network/NetworkUtility.h>
#include <Libwiisys/logging/WebLogger.h>
#include <Libwiisys/logging/GeckoLogger.h>
#include <Libwiisys/logging/FileLogger.h>
#include <Libwiisys/logging/Log.h>
#include <Libwiisys/Exceptions/Exception.h>
#include <Libwiisys/Serialization/Xml.h>
#include <Libwiisys/String/UtilString.h>

using namespace std;
using namespace Libwiisys;
using namespace Libwiisys::Network;
using namespace Libwiisys::Logging;
using namespace Libwiisys::Serialization;
using namespace Libwiisys::String;
using namespace Libwiisys::Exceptions;

Config::Config() :
    _hasNetwork(false)
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

void Config::Initialize(const string& configFilePath)
{
  Config& c = Instance();

  if (Config::HasNetwork())
  {
    WebLogger* sciifiiLog = new WebLogger(
                              "http://www.teamwiigen.fr.cr/WebLogging/Logger.aspx",
                              "message", "line", "file", "application", "version");
    Log::AddLogProvider(Lgt_All, sciifiiLog);
  }

  TiXmlDocument& doc = Xml::Load(configFilePath);
  TiXmlElement* root = doc.RootElement();

  if (string(root->Attribute("version")) != SCIIFII_VERSION || string(
        root->Value()) != "sciifii")
    throw Exception("Config file version not supported");

  c._menuMessage = root->Attribute("MenuMessage");
  c._workingDirectory = UtilString::ToStr(root->Attribute("workingDirectory"), "sd:/sciifii/temp/");
	c._themeDirectory = UtilString::ToStr(root->Attribute("themeDirectory"), "");
	
  TiXmlElement* child = root->FirstChildElement();

  while (child != NULL)
  {
    if (child->Type() != TiXmlElement::COMMENT)
    {
      string nodeValue = UtilString::ToStr(child->Value());

      if (nodeValue == "logs")
        c.CreateLogs(child);
      else if (nodeValue == "files")
        FileManager::Init(child);
      else if (nodeValue == "steps")
        c.CreateStepList(child);
      else if (nodeValue == "Disclaimer")
        c._disclaimer = UtilString::Replace(UtilString::ToStr(child->FirstChild()->Value(), ""), "\\n", "\n");
      else if (nodeValue == "menus")
      {
#ifdef USE_ADVANCED_UI
        GMenuManager::Instance(child);
#else

        MenuManager::Instance(child);
#endif

      }
      else
        throw Exception("Invalid XmlNode.");
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
        throw Exception("options child node is invalid");

      string type = UtilString::ToStr(child->Attribute("type"));
      string cat = UtilString::ToStr(child->Attribute("category"), "all");
      string path = UtilString::ToStr(child->Attribute("path"), "");
      string url = UtilString::ToStr(child->Attribute("url"), "");
      LogType t;
      if (cat == "error")
        t = Lgt_Error;
      else if (cat == "warning")
        t = Lgt_Warning;
      else if (cat == "info")
        t = Lgt_Info;
      else if (cat == "all")
        t = Lgt_All;
      else if (cat == "debug")
        t = Lgt_Debug;
      else
        throw Exception("Invalid log category : " + cat);

      if (type == "file")
      {
        if (path == "")
          throw Exception("File logger needs a file path !");

        FileLogger* l = new FileLogger(path);
        Log::AddLogProvider(t, l);
      }
      else if (type == "gecko")
      {
        GeckoLogger* g = new GeckoLogger();
        Log::AddLogProvider(t, g);
      }
      else if (type == "web" && _hasNetwork)
      {
        if (url == "")
          throw Exception("Weblogger needs an url for logging!");
        WebLogger *sciifiiLog = new WebLogger(url, "message", "line",
                                              "file", "application", "version");
        Log::AddLogProvider(t, sciifiiLog);
      }
      else
        throw Exception("Invalid log type : " + type);
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

      for (vector<u32>::iterator ite = step->Region().begin(); ite != step->Region().end(); ite++)
        if (*ite == GetRegion())
        {
          addToList = true;
        }

      if (addToList)
        _availableSteps.push_back(step);
      else
        delete step;
    }

    child = child->NextSiblingElement();
  }

}

void Config::ValidateOptions()
{
  /*cout << "\x1b[2J";
  cout << "\x1b[2;0H";
  cout << "Sciifii is analysing your choice" << endl;*/
  vector<Installer*> steps = Instance()._availableSteps;

  for (vector<Installer*>::iterator step = steps.begin(); step != steps.end(); step++)
  {
    bool validated = false;

    if ((*step)->Options() == "")
      validated = true;
    else
    {
      vector<string> switches = UtilString::Split((*step)->Options(), '|');

      for (vector<string>::iterator ite = switches.begin(); ite != switches.end(); ite++)
      {
        if (Instance()._switches.find(*ite) != Instance()._switches.end())
        {
          validated = true;
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

u32 Config::GetRegion()
{
  return Instance()._region;
}


void Config::SetSwitch(const Switch& s)
{
  if(s.Activated)
    Instance()._switches[s.Name] = s.Value;
  else
    Instance()._switches.erase(s.Name);
}

void Config::ClearSwitches()
{
  Instance()._switches.clear();
}

void Config::Reset()
{
  ClearSwitches();
  Instance()._validatedSteps.clear();
}

string Config::ThemeDirectory()
{
	return Instance()._themeDirectory;
}