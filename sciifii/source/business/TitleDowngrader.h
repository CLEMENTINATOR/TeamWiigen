#ifndef _IOSDOWNGRADER_H_
#define _IOSDOWNGRADER_H_

#include <libutils/events/TitleEventArgs.h>
#include "common/Installer.h"

class TitleDowngrader : public Installer
{
private:
	u64 _id;
	u16 _neededRevision;

	void DowngradeTmd(Object* sender, TitleEventArgs *args);
	void SkipStep(Object* sender, TitleEventArgs *args);

public:
	TitleDowngrader(u64 titleId, u16 neededRevision);
	bool Prepare();
	void Install();
	void SendToLog();
};

#endif
