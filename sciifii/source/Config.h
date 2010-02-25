#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <gctypes.h>
#include <string>
#include <libutils/Object.h>
#include <vector>
#include <tinyxml.h>
#include "business/common/Installer.h"

#define SCIIFII_VERSION "2"

typedef struct
{
	u64 destId;
	u64 sourceId;
	u16 revision;
	u16 dipVersion;
	u16 esVersion;
	bool IdentifyPatch;
	bool NandPatch;
	bool KoreanPatch;
	bool localOnly;
} ciosDesc;

typedef struct
{
	u64 slot;
	u64 title;
	u16 revision;
	bool onlyOnUninstall;
} titleDescriptor;

typedef struct
{
	std::string name;
	std::string text;
	bool selected;
} option;

typedef struct
{
	std::vector<std::string> options;
	std::string text;
	std::string flag;
} mode;

class Config : public Object
{
private:
	s32 _region;
	bool _hasNetwork;

	bool _uninstall;

	std::string _menuMessage;
	std::string _workingDirectory;
	bool _useAdvancedSettings;
	std::string _disclaimer;

	std::vector<ciosDesc> _corp;
	std::vector<titleDescriptor> _systemTitleList;
	std::vector<titleDescriptor> _updateList;

	std::vector<option*> _options;
	std::vector<mode*> _modes;
	std::vector<Installer*> _availableSteps;
	std::vector<Installer*> _validatedSteps;

	Config();
	static Config& Instance();
	static std::vector<std::string> GetOptionList(const std::string& options);
	void CreateCorpList(TiXmlElement* element);
	void CreateUpdateList(TiXmlElement* element);
	void CreateOptionList(TiXmlElement* element);
	void CreateModeList(TiXmlElement* element);
	void CreateStepList(TiXmlElement* element);
public:
	static void Initialize();
	static void ApplyMode(const mode& m);
	static void ValidateOptions();

	static std::string WorkingDirectory();
	static bool HasNetwork();
	static std::vector<mode*> Modes();
	static std::vector<option*> Options();
	static std::vector<Installer*> Steps();
	static std::vector<ciosDesc> CorpConfiguration();
	static std::vector<titleDescriptor> UpdateConfiguration();
	static std::string MenuMessage();
	static std::string DisclaimerText();
	static bool UseAdvancedMode();
};

#endif
