#ifndef SCIIFII_H_
#define SCIIFII_H_

#include <vector>
#include <libutils/Object.h>
#include "business/common/Installer.h"

class Sciifii : public Object
{
private:
	std::vector<Installer*> steps;

public:
	Sciifii();
	~Sciifii();
	void DisplayProgress(Object* sender, ProgressEventArgs* args);
	bool Prepare();
	void Execute();
};

#endif /* SCIIFII_H_ */
