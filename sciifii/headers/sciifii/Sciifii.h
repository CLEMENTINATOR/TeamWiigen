#ifndef SCIIFII_H_
#define SCIIFII_H_

#include <string>
#include <vector>
#include <libwiisys.h>
#include "business/common/Installer.h"

class Sciifii : public Libwiisys::Object
{
private:
	void DisplayProgress(Libwiisys::Object* sender, Libwiisys::Threading::ProgressEventArgs* args);

	bool hasDisplayed;
public:
	Sciifii();
	bool Prepare();
	void Execute();
	static std::string& LastStepMessage();
};

#endif /* SCIIFII_H_ */
