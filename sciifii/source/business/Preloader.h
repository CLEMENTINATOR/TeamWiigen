#ifndef PRELOADER_H_
#define PRELOADER_H_

#include <gctypes.h>

class Preloader
{
private:
    u32 bootCid;
public:
	Preloader();
	void Prepare();
	void Install();
};

#endif
