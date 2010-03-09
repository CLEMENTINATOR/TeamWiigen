#include <Dol.h>
#include <fs/File.h>
#include <exception/Exception.h>

#include <gccore.h>
#include <ogc/machine/asm.h>
#include <ogc/machine/processor.h>
#include <string.h>

using namespace std;

/**
 * \brief Execute the dol file
 *
 * \param path The full path of the dol file
 * \param physicalAddres The memory adress where to store temp datas
 */
void Dol::Execute(const string &path, void* physicalAddress)
{
	Dol d(path, physicalAddress);
	d.LoadDol();
	d.Run();

	//we shouldn't access here
	throw Exception("Error launching dol file", -1);
}

/**
 * \brief Execute the dol file
 *
 * \param physicalAddress The memory adress where the dol file will be stored
 * \param content A buffer that contain the Dol representation
 * \param contentLength The length of the dol buffer
 */
void Dol::Execute(void* physicalAddress, void *content, u64 contentLength)
{
	Dol d(content, physicalAddress, contentLength);
	d.LoadDol();
	d.Run();

	//we shouldn't access here
	throw Exception("Error launching dol file", -1);
}

/**
 * \brief Load the file to a temp buffer
 *
 * \param path The full path of the dol file
 * \param physicalAddress The temp adress where to store the dol
 */
Dol::Dol(const std::string &path, void* physicalAddress)
  : content(physicalAddress)
{
    File &dolFile = File::Open(path, FileMode_Read);
	
    if(dolFile.Read(content,dolFile.Size()) != dolFile.Size())
    {
    	dolFile.Close();
    	delete &dolFile;
		throw Exception("Error reading the dol file.", -1);
    }

    dolFile.Close();
    delete &dolFile;
}

/**
 * \brief Load a dol to a temp buffer
 *
 * \param content The dol representation
 * \param physicalAddress The temp buffer adress
 * \param contentLength The length of the dol
 */
Dol::Dol(void *content, void* physicalAddress, u64 contentLength)
{
	if(contentLength > 0)
		memcpy(physicalAddress, content, contentLength);

	this->content = physicalAddress;
}

/**
 * \brief Load the dol to its execution memory adress
 */
void Dol::LoadDol()
{
	dolheader *dolfile = (dolheader*)content.Content();
	for (u32 textIndex = 0; textIndex < 7; textIndex++)
	{
		//si l'item i existe et est en position > 0x100
		if (!dolfile->text_size[textIndex] || dolfile->text_start[textIndex] < 0x100)
			continue;

		char* text = (char*)dolfile + dolfile->text_pos[textIndex];

		ICInvalidateRange((void*)dolfile->text_start[textIndex], dolfile->text_size[textIndex]);
		memmove((void*)dolfile->text_start[textIndex], text, dolfile->text_size[textIndex]);
	}

	for(u32 dataIndex = 0; dataIndex < 11; dataIndex++)
	{
		if (!dolfile->data_size[dataIndex] || dolfile->data_start[dataIndex] < 0x100)
			continue;

		char* data = (char*)dolfile + dolfile->data_pos[dataIndex];

		memmove ((void*)dolfile->data_start[dataIndex], data, dolfile->data_size[dataIndex]);
		DCFlushRangeNoSync ((void*)dolfile->data_start[dataIndex], dolfile->data_size[dataIndex]);
	}

	memset((void*)dolfile->bss_start, 0, dolfile->bss_size);
	DCFlushRange((void*)dolfile->bss_start, dolfile->bss_size);
}

/**
 * \brief Jump to the start adress of the dol
 */
void Dol::Run()
{
	dolheader *dolfile = (dolheader*)content.Content();
	void (*ep)() = (void(*)())dolfile->entry_point;

	// code from geckoloader
	u32 level;
	__IOS_ShutdownSubsystems ();
	_CPU_ISR_Disable (level);
	__exception_closeall ();
	ep();
	_CPU_ISR_Restore (level);
}
