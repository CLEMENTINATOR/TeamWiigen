#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <gctypes.h>
#include <string>
#include <Libwiisys/Object.h>
#include <vector>
#include <tinyxml.h>
#include "business/common/Installer.h"
#include <map>
#include "Switch.h"

#define SCIIFII_VERSION "5"

class Config : public Libwiisys::Object
{
  private:
    s32 _region;
    bool _hasNetwork;
	std::string _uiMode;

    std::map<std::string,std::string> _switches;

    std::string _menuMessage;
    std::string _workingDirectory;
    std::string _disclaimer;
	std::string _themeDirectory;

    std::vector<Installer*> _availableSteps;
    std::vector<Installer*> _validatedSteps;

    Config();
    static Config& Instance();
    void CreateLogs(TiXmlElement* element);
    void CreateStepList(TiXmlElement* element);
  public:
    static void Initialize(const std::string& configFilePath);
    static void ValidateOptions();
    static u32 GetRegion();
    static void SetSwitch(const Switch& s);
    static void ClearSwitches();
    static std::string WorkingDirectory();
    static bool HasNetwork();
    static bool AutoClean();
    static std::vector<Installer*> Steps();
    static std::string MenuMessage();
    static std::string DisclaimerText();
	static std::string ThemeDirectory();
    static void Reset();
	static bool IsUiMode();
};

#endif
