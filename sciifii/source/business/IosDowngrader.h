#ifndef _IOSDOWNGRADER_H_
#define _IOSDOWNGRADER_H_

#include <libutils/events/TitleEventArgs.h>
#include "common/Installer.h"

class IosDowngrader : public Installer
{
private:
	u64 _id;
	u16 _neededRevision;

	void DowngradeTmd(Object* sender, TitleEventArgs *args);
	void SkipStep(Object* sender, TitleEventArgs *args);

public:
	IosDowngrader(u32 titleId, u16 neededRevision);
	bool Prepare();
	void Install();
};

#endif
