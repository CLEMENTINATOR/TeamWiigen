#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <gctypes.h>
#include <string>
#include <libwiisys.h>
#include <vector>
#include <tinyxml.h>
#include "business/common/Installer.h"

#define SCIIFII_VERSION "4"

typedef struct
{
	std::string name;
	std::string text;
	bool selected;
	bool hidden;
} option;

typedef struct
{
	std::vector<std::string> options;
	std::string text;
} mode;

class Config : public Libwiisys::Object
{
private:
	s32 _region;
	bool _hasNetwork;

	std::string _menuMessage;
	std::string _workingDirectory;
	bool _useAdvancedSettings;
	std::string _disclaimer;

	std::vector<option*> _options;
	std::vector<mode*> _modes;
	std::vector<Installer*> _availableSteps;
	std::vector<Installer*> _validatedSteps;

	Config();
	static Config& Instance();
	 void CreateLogs(TiXmlElement* element);
	void CreateOptionList(TiXmlElement* element);
	void CreateModeList(TiXmlElement* element);
	void CreateStepList(TiXmlElement* element);
public:
	static void Initialize(const std::string& configFilePath);
	static void ApplyMode(const mode& m);
	static void ValidateOptions();
	static u32 GetRegion();

	static std::string WorkingDirectory();
	static bool HasNetwork();
	static bool AutoClean();
	static std::vector<mode*> Modes();
	static std::vector<option*> Options();
	static std::vector<Installer*> Steps();
	static std::string MenuMessage();
	static std::string DisclaimerText();
	static bool UseAdvancedMode();
};

#endif
