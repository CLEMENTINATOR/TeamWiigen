#ifndef _TITLE_MODULE_H_
#define _TITLE_MODULE_H_

#include "../../Buffer.h"
namespace Libwiisys {
	namespace System {
		namespace Patching {

			/**
			 * \class TitleModule
			 * \brief Class used to patch title modules
			 * \author Arasium,Teton,Fanta
			 * \version 1.0
			 */
			class TitleModule : public Buffer
			{
			private:
				s32 _position;

			public:
				/**
				 * @brief Constructor
				 * @param buffer A Buffer containing the patched module
				 * @param requiredPosition Optionnal parameter, set this if you want to patch the module in a specific place
				 */
				TitleModule(const Buffer& buffer, const s32 requiredPosition = -1);

				/**
				 * @brief Constructor
				 * @param buffer The buffer containing the module
				 * @param length The length of the buffer
				 * @param requiredPosition Optionnal parameter if you want to set the module to an other position(or overide a module )
				 */
				TitleModule(const u8* buffer, const u64 length, const s32 requiredPosition = -1);

				/**
				 * @brief Copy Constructor
				 * @param module The TitleModule to copy
				 * @return The copied TitleModule
				 */
				TitleModule(const TitleModule& module);

				/**
				 * @brief Check if a position is required
				 * @return true if a position is required
				 */
				bool IsPositionRequired() const;

				/**
				 * @brief Return the required position of the module
				 * @return The required position of the module , else -1
				 */
				u32 Position() const;
			};
		}
	}
}
#endif
