#ifndef WADBATCH_H_
#define WADBATCH_H_

#include "common/Installer.h"
#include "TitleStep.h"

class WadBatch : public Installer
{
private:
	std::string _wadFolder;
	TitleAction a;

public:
	WadBatch(const std::string &folder,TitleAction action);
	bool Prepare();
	void Install();
	void SendToLog();
};

#endif
