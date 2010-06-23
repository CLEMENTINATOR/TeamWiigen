#ifndef DOL_H_INCLUDED
#define DOL_H_INCLUDED

#include <string>
#include <ogcsys.h>
#include "Object.h"
#include "com/Buffer.h"
#include "dol_header.h"

extern "C" { void __exception_closeall(); }

namespace Libwiisys { namespace Shell {

/*! \class Dol
 * \brief This class allow the loading/launching of Dol files.
 * \author Arasium, Teton, Fanta
 * \version 1.0
 *
 * The Dol class allow the user to execute a Dol file. The Dol can be specified using the Dol
 * file path, or using a buffer.
 * The Dol representation is stored in memory at the specified address.
 */
class Dol : public Object
{
public :
	static void Execute(const std::string &path, void* physicalAddress);
	static void Execute(void* physicalAddress, void* content = NULL, u64 contentLength = 0);
private:
	dolheader* dolbegin;
	Buffer content;
	Dol(const std::string &path, void* physicalAddress);
	Dol(void* content, void* physicalAddress, u64 contentLength);
	void LoadDol();
	void Run();
};

}}

#endif // DOL_H_INCLUDED
