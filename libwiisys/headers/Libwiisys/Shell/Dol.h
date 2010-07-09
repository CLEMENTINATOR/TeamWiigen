#ifndef DOL_H_INCLUDED
#define DOL_H_INCLUDED

#include <string>
#include <ogcsys.h>
#include "../Object.h"
#include "../Buffer.h"
#include "dol_header.h"

extern "C" {void __exception_closeall();}

/*! \namespace Libwiisys::Shell
 * \brief Executables and commands
 *
 * This namespace aim to provide a set of tools used to run
 * executables.
 */
namespace Libwiisys {namespace Shell {

		/**
		 * \class Dol
		 * \brief This class allow the loading/launching of Dol files.
		 * \author Arasium, Teton, Fanta
		 * \version 1.0
		 */
		class Dol : public Object
		{
		public :

			/**
			 * \brief Execute the dol file
			 * \param path The full path of the dol file
			 * \param physicalAddress The memory address where to store temporary data
			 */
			static void Execute(const std::string &path, void* physicalAddress);

			/*
			 static void Execute(void* physicalAddress, void* content = NULL, u64 contentLength = 0);
			 */
		private:
			dolheader* dolbegin;
			Buffer content;

			/**
			 * \brief Load the file to a temp buffer
			 * \param path The full path of the dol file
			 * \param physicalAddress The temp adress where to store the dol
			 */
			Dol(const std::string &path, void* physicalAddress);

			/*
			 Dol(void* content, void* physicalAddress, u64 contentLength);
			 */
			/**
			 * \brief Load the dol to its execution memory adress
			 */
			void LoadDol();

			/**
			 * \brief Jump to the start adress of the dol
			 */
			void Run();
		};

	}}

#endif // DOL_H_INCLUDED
