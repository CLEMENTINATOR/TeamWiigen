#include <Elf.h>
#include <fs/File.h>
#include <exception/Exception.h>
#include <elf_abi.h>
#include <gccore.h>
#include <ogc/machine/asm.h>
#include <ogc/machine/processor.h>
#include <string.h>
#include <stdlib.h>

using namespace Libwiisys::Shell;

/**
 * \brief Load the file to a temp buffer
 *
 * \param path The full path of the elf file
 * \param physicalAddress The temp adress where to store the elf
 */
Elf::Elf(const std::string &path, void* physicalAddress)
  : content(physicalAddress)
{
    File &elfFile = File::Open(path, FileMode_Read);

    if(elfFile.Read(content,elfFile.Size()) != elfFile.Size())
    {
    	elfFile.Close();
    	delete &elfFile;
		throw Exception("Error reading the dol file.", -1);
    }

    elfFile.Close();
    delete &elfFile;
}

/**
 * \brief Execute the elf file
 *
 * \param path The full path of the elf file
 * \param physicalAddress The memory adress where to store temp datas
 */
void Elf::Execute(const std::string &path, void* physicalAddress)
{
	Elf e(path, physicalAddress);
	if (!e.Validate())
		throw Exception("Not a valid elf file !", -1);

	e.LoadElf();
	e.Run();

	//we shouldn't access here
	throw Exception("Error launching Elf file", -1);
}

/**
 * \brief Validate the elf file
 *
 * \return true is it a valid elf file, else false
 */
bool Elf::Validate ()
{
        Elf32_Ehdr *ehdr; /* Elf header structure pointer */

        ehdr = (Elf32_Ehdr *) content.Content();

        if (!IS_ELF (*ehdr))
                return false;

        if (ehdr->e_type != ET_EXEC)
                return false;

        if (ehdr->e_machine != EM_PPC)
                return false;

        return true;
}

/**
 * \brief Load the elf to its execution memory adress
 */
void Elf::LoadElf()
{
	Elf32_Ehdr *elfHeader = (Elf32_Ehdr *) content.Content();
	u32 sectionHeaderSize = sizeof (Elf32_Shdr);
	/* Load each appropriate section */
	for (int sectionIndex = 0; sectionIndex < elfHeader->e_shnum; ++sectionIndex)
	{
		Elf32_Shdr *sectionTable = (Elf32_Shdr *) ((char*)elfHeader + elfHeader->e_shoff + sectionIndex * sectionHeaderSize);

		if (!(sectionTable->sh_flags & SHF_ALLOC) || sectionTable->sh_addr == 0 || sectionTable->sh_size == 0)
			continue;

		sectionTable->sh_addr &= 0x3FFFFFFF;
		sectionTable->sh_addr |= 0x80000000;


		if (sectionTable->sh_type == SHT_NOBITS)
			memset ((void*) sectionTable->sh_addr, 0, sectionTable->sh_size);
		else
		{
				u8 *image = (u8*)elfHeader + sectionTable->sh_offset;
				memcpy ((void*)sectionTable->sh_addr, (void*)image, sectionTable->sh_size);
		}
		DCFlushRangeNoSync ((void*)sectionTable->sh_addr, sectionTable->sh_size);
	}

	exeEntryPoint = (elfHeader->e_entry & 0x3FFFFFFF) | 0x80000000;
}

/**
 * \brief Jump to the executable entry point
 */
void Elf::Run()
{

	void (*ep)() = (void(*)())exeEntryPoint;
	// code from geckoloader
	u32 level;
	__IOS_ShutdownSubsystems ();
	_CPU_ISR_Disable (level);
	__exception_closeall ();
	ep();
	_CPU_ISR_Restore (level);








}

