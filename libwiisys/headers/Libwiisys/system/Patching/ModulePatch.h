#ifndef _SYSTEM_MODULE_PATCH_H_
#define _SYSTEM_MODULE_PATCH_H_

#include <ogcsys.h>
#include <string>
#include "../../Buffer.h"
#include "../Event/TitleEventArgs.h"
#include "Patch.h"
namespace Libwiisys {
	namespace System {
		namespace Patching {

			/**
			 * \class ModulePatch
			 * \brief Handles module patching
			 * \author Arasium,Teton,Fanta
			 * \version 1.0
			 */
			class ModulePatch : public Patch
			{
			private:
				u8* _patch;
				u32 _length;

			protected:

				/**
				 * @brief Patch
				 * @param processControl the TitleEventArgs with the data to patch ( throw by events)
				 * @return 1
				 */
				u32 Patching(System::Event::TitleEventArgs &processControl) const;

			public:

				/**
				 * @brief Constructor
				 * @param patch A patch for rewriting a module
				 * @param length the length of the patch
				 * @param module The name of the module to rewrite
				 */
				ModulePatch(const u8* patch, const u32 length, const std::string &module = "");

				/**
				 * @brief Copy Constructor
				 * @param patch An other ModulePatch object
				 */
				ModulePatch(const ModulePatch& patch);

				/**
				 * Destructor
				 */
				virtual ~ModulePatch();

				/**
				 * @brief Overloaded =() operator
				 * @param patch The patch to copy ( data are copied)
				 * @return The ModulePatch set to patch
				 */
				ModulePatch& operator=(const ModulePatch& patch);
			};
		}
	}
}
#endif
