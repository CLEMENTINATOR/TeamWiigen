#ifndef _SYSTEM_PLUGIN_PATCH_H_
#define _SYSTEM_PLUGIN_PATCH_H_

#include <ogcsys.h>
#include <string>
#include <vector>
#include "../../Buffer.h"
#include "../Event/TitleEventArgs.h"
#include "Patch.h"
#include "SimplePatch.h"
#include "../../Shell/elf_abi.h"
namespace Libwiisys {namespace System {namespace Patching {
			/**
			 * @struct ArmHeader
			 * @brief ARM binary header structure
			 */
			typedef struct {
				/** HeaderSize */
				u32 headerSize;
				/** offset of the beginning of the elf file */
				u32 offset;
				/** size of the elf file*/
				u32 size;
				/** reserved */
				u32 resevered;
			}ArmHeader;

			/**
			 * \class PluginPatch
			 * \brief Handles plugin patching
			 * \author Arasium,Teton,Fanta
			 * \version 1.0
			 */
			class PluginPatch : public Patch
			{

			private:
				Buffer _plugin;
				u32 _offset;
				u32 _bssNewSize;
				std::vector<SimplePatch> _commandHandles;
				Elf32_Phdr* _newProgramSection;
				u32 _replaceSection;

				bool IsElf(u8* buffer) const;
				u32 FindIOSVersionIndex(const Buffer& b) const;
				u32 FindPlugedSegment(u8* elf, u32 moduleToSkip) const;
				u32 FindBssSegment(u8* elf, u32 moduleToSkip) const;
				u32 FindSegmentSize(u8* elf, u32 segmentIndex) const;
				u64 GetElfSize(const u8* elf) const;
				void Plug(u32 segmentIndex, u32 bssSegmentIndex, u8* source, u8* dest) const;
				void Plug(u32 segmentIndex, u8* source, u8* dest) const;

			protected:
				u32 Patching(Libwiisys::System::Event::TitleEventArgs &processControl) const;

			public:
                    virtual std::string GetType();
				/**
				 * @brief Constructor
				 * @param plugin The patched plugin
				 * @param offset The offset where to patch the plugin
				 * @param bssNewSize The new size of the bss part
				 * @param module The module where it'll apply the patch
				 */
				PluginPatch(const Buffer& plugin, const u32 offset, const u32 bssNewSize, const std::string &module);

				/**
				 * @brief Constructor
				 * @param plugin The plugin to patch
				 * @param newHeader The new elf header
				 * @param module the module to patch
				 * @param replaceSection The section to replace, or 0 to add a new one
				 */
				PluginPatch(const Buffer& plugin, Elf32_Phdr newHeader , const std::string &module, u32 replaceSection = 0);

				/**
				 * @brief Copy Constructor
				 * @param patch the patch to copy
				 * @return The copied patch
				 */
				PluginPatch(const PluginPatch& patch);
				virtual ~PluginPatch();

				/**
				 * @brief Overloaded = operator
				 * @param patch The patch to copy
				 * @return the copied patch
				 */
				PluginPatch& operator=(const PluginPatch& patch);

				/**
				 * @brief Defines command handles
				 * @param handle A command handle to patch
				 */
				void DefineCommandHandle(SimplePatch handle);
			};
		}
	}
}
#endif
