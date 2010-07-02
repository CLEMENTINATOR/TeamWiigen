#ifndef ELF_H_INCLUDED
#define ELF_H_INCLUDED

#include <string>
#include <ogcsys.h>
#include "../Object.h"
#include "../Buffer.h"

extern "C" { void __exception_closeall(); }

namespace Libwiisys { namespace Shell {

/**
 * \class Elf
 * \brief This class allow the loading/launching of Elf files.
 * \author Arasium, Teton, Fanta
 * \version 1.0
 */
class Elf : public Object
{
public :
	static void Execute(const std::string &path, void* physicalAddress);
private :
	Elf(const std::string &path, void* physicalAddress);
	void LoadElf();
	void Run();
	Buffer content;
	u32 exeEntryPoint;
	bool Validate();
};

}}
#endif
