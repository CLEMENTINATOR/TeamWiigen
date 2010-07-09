#ifndef ELF_H_INCLUDED
#define ELF_H_INCLUDED

#include <string>
#include <ogcsys.h>
#include "../Object.h"
#include "../Buffer.h"

extern "C" {void __exception_closeall();}

namespace Libwiisys {namespace Shell {

		/**
		 * \class Elf
		 * \brief This class allow the loading/launching of Elf files.
		 * \author Arasium, Teton, Fanta
		 * \version 1.0
		 */
		class Elf : public Object
		{
		public :

			/**
			 * \brief Execute the elf file
			 * \param path The full path of the elf file
			 * \param physicalAddress The memory adress where to store the elf data
			 */
			static void Execute(const std::string &path, void* physicalAddress);

		private :
			Buffer content;
			u32 exeEntryPoint;
			/**
			 * \brief Load the file to a temp buffer
			 * \param path The full path of the elf file
			 * \param physicalAddress The temp adress where to store the elf data
			 */
			Elf(const std::string &path, void* physicalAddress);

			/**
			 * \brief Load the elf to its execution memory adress
			 */
			void LoadElf();

			/**
			 * \brief Jump to the executable entry point
			 */
			void Run();

			/**
			 * \brief Validate the elf file
			 * \return true is it a valid elf file, else false
			 */
			bool Validate();
		};

	}}
#endif
