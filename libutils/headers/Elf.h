#ifndef ELF_H_INCLUDED
#define ELF_H_INCLUDED

#include <string>
#include <ogcsys.h>
#include "Object.h"
#include "com/Buffer.h"

typedef void (*entrypoint) (void);
extern "C" { void __exception_closeall(); }

/*! \class Elf
 * \brief This class allow the loading/launching of Elf files.
 * \author Arasium, Teton, Fanta
 * \version 1.0
 *
 * The Elf class allow the user to execute a elf file. The Elf can be specified using the Elf
 * file path, or using a buffer.
 * The Elf representation is stored in memory at a specified address.
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
#endif
