#ifndef _SYSTEM_PATCH_H_
#define _SYSTEM_PATCH_H_

#include <ogcsys.h>
#include <list>
#include <string>
#include "../Object.h"
#include "../com/Buffer.h"
#include "../events/TitleEventArgs.h"

class Patch : public Object
{
private:	
	bool IsModule(const Buffer& b, const std::string &module) const;
	bool CanPatch(const Buffer& b) const;

protected:
	virtual u32 Patching(TitleEventArgs &processControl) const = 0;
	
public:	
	std::string AllowedModule;
	std::string ForbiddenModule;
	
	Patch(const std::string &module = "");
	Patch(const Patch& patch);
	~Patch();
	
	Patch& operator=(const Patch& patch);
	u32 ApplyPatch(TitleEventArgs &processControl) const;
};

#endif
