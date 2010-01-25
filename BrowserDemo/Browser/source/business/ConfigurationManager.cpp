#include <stdlib.h>

#include "ConfigurationManager.h"

ConfigurationManager::ConfigurationManager()
{
	ensureSecurity = true;
}

ConfigurationManager &ConfigurationManager::GetCurrent()
{
	static ConfigurationManager current;
	return current;
}

bool ConfigurationManager::IsEnSureSecurity() const
{
	return ensureSecurity;
}

void ConfigurationManager::SetEnsureSecurity(const bool &ensureSecurity)
{
	this->ensureSecurity = ensureSecurity;
}

