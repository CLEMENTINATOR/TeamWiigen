#ifndef SCIIFII_H_
#define SCIIFII_H_

#include <string>
#include <vector>
#include <libutils/Object.h>
#include "business/common/Installer.h"

class Sciifii : public Object
{
private:
	void DisplayProgress(Object* sender, ProgressEventArgs* args);

	bool hasDisplayed;
public:
	Sciifii();
	~Sciifii();
	bool Prepare();
	void Execute();
	static std::string& LastStepMessage();
};

#endif /* SCIIFII_H_ */
