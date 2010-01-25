#ifndef _CONFIGURATIONMANAGER_H_
#define _CONFIGURATIONMANAGER_H_

class ConfigurationManager
{
private:
	bool ensureSecurity;
	ConfigurationManager();
public:
	static ConfigurationManager &GetCurrent();
	bool IsEnSureSecurity() const;
	void SetEnsureSecurity(const bool &ensureSecurity);
};

#endif
