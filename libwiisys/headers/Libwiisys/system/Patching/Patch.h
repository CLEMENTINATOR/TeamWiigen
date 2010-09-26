#ifndef _SYSTEM_PATCH_H_
#define _SYSTEM_PATCH_H_

#include <ogcsys.h>
#include <list>
#include <string>
#include "../../Object.h"
#include "../../Buffer.h"
#include "../Event/TitleEventArgs.h"
namespace Libwiisys {
	namespace System {
		namespace Patching {

			/**
			 * \class Patch
			 * \brief Handles patching
			 * \author Arasium,Teton,Fanta
			 * \version 1.0
			 *
			 * Handles patching(inherited by all patch classes)
			 */
			class Patch : public Object
			{

			private:

				/**
				 * @brief Check is the module is the good one
				 * @param b The buffer containing the module
				 * @param module The name of the module
				 * @return true is b is containing the module module
				 */
				bool IsModule(const Buffer& b, const std::string &module) const;

				/**
				 * @brief Check if can patch
				 * @param b The buffer to patch
				 * @return true if possible to patch
				 */
				bool CanPatch(const Buffer& b) const;

			protected:

				/**
				 *@brief Patch
				 *@param processControl The TitleEventArgs where is the data to patch
				 *@return Nothing interesting (1)
				 */
				virtual u32 Patching(Libwiisys::System::Event::TitleEventArgs &processControl) const = 0;

			public:

			virtual std::string GetType();
				/** AllowedModule to patch */
				std::string AllowedModule;

				/** ForbiddenModule to patch */
				std::string ForbiddenModule;

				/**
				 * @brief Constructor
				 * @param module The module where the patch will be applied(default is ""(none))
				 */
				Patch(const std::string &module = "");

				/**
				 * @brief Copy constructor
				 * @param patch The patch to copy
				 */
				Patch(const Patch& patch);

				/**
				 * @brief Destructor
				 */
				virtual ~Patch();

				/**
				 * @brief Overloaded = operator
				 * @param patch The patch to copy
				 * @return A new patch set to patch values
				 */
				Patch& operator=(const Patch& patch);

				/**
				 * @brief Apply the patch
				 * @param processControl The TitleEventArgs where is the data to patch
				 * @return 1
				 */
				u32 ApplyPatch(Libwiisys::System::Event::TitleEventArgs &processControl) const;
			};
		}
	}
}
#endif
