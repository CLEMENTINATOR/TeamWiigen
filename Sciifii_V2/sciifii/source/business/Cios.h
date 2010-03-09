#ifndef _CIOS_H_
#define _CIOS_H_

#include <string>
#include <fastdelegate.h>
#include <libutils/system/SimplePatch.h>

#include "common/Installer.h"

class Cios : public Installer
{
private:
	static SimplePatch* DIP_Cmd1();
	static SimplePatch* DIP_Cmd2();
	
	static SimplePatch* FFS_OpenCmd();
	static SimplePatch* FFS_CloseCmd();
	static SimplePatch* FFS_ReadCmd();
	static SimplePatch* FFS_WriteCmd();
	static SimplePatch* FFS_SeekCmd();
	static SimplePatch* FFS_IoctlCmd();
	static SimplePatch* FFS_IoctlvCmd();
	
	static SimplePatch* ES_Cmd();
public:
	bool Prepare();
	void Install();
};
#endif
