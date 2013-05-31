#ifndef _SYSTEM_SIMPLE_PATCH_H_
#define _SYSTEM_SIMPLE_PATCH_H_

#include <ogcsys.h>
#include <string>
#include "Patch.h"

namespace Libwiisys
{
  namespace System
  {
    namespace Patching
    {

      /**
       * \class SimplePatch
       * \brief Handles simple patching
       * \author Arasium,Teton,Fanta
       * \version 1.0
       * This class can use already existing patch or create some
       */

      class SimplePatch : public Patch
      {

        private:
          u8* _pattern;
          u8* _patch;
          u32 _length;
          u32 _offset;

        protected:
          u32 Patching(Libwiisys::System::Event::TitleEventArgs &processControl) const;

        public:
          virtual std::string GetType();
          /**
           * @brief Constructor
           * @param pattern The pattern to patch
           * @param patch The patch
           * @param length The patch lentgh
           * @param module The module name to patch ( default = "" ( none))
           */
          SimplePatch(const u8* pattern, const u8* patch, const u32 length, const std::string &module = "");
          
          
          /**
           * @brief Constructor
           * @param pattern The pattern to patch
           * @param patch The patch
           * @param length The patch lentgh
           * @param module The module name to patch ( default = "" ( none))
           * @param offset offset for the patch
           */
          SimplePatch(const u8* pattern, const u8* patch, const u32 length, const u32 offset, const std::string &module = "");

          /**
           * @brief Copy Constructor
           * @param patch The patch to copy
           * @return The copied patch
           */
          SimplePatch(const SimplePatch& patch);
          virtual ~SimplePatch();

          /**
           * @brief Overloaded = operator
           * @param patch The patch to copy
           * @return The copied Patch
           */
          SimplePatch& operator=(const SimplePatch& patch);

          /* ES Patches */
          /** Prebuild patch */
          static SimplePatch* ES_HashCheck_Old();

          /** Prebuild patch */
          static SimplePatch* ES_HashCheck_New();

          /** Prebuild patch */
          static SimplePatch* ES_Identify();

          /** Prebuild patch */
          static SimplePatch* ES_OpenTitleContent1();

          /** Prebuild patch */
          static SimplePatch* ES_OpenTitleContent2();

          /** Prebuild patch */
          static SimplePatch* ES_ReadContent();

          /** Prebuild patch */
          static SimplePatch* ES_CloseContent();

          /** Prebuild patch */
          static SimplePatch* ES_SetUIDCheck();

          /** Prebuild patch */
          static SimplePatch* ES_TitleVersionCheck();

          /** Prebuild patch */
          static SimplePatch* ES_TitleDeleteCheck();

          /** Prebuild patch */
          static SimplePatch* ES_MEM2Protection();

          /* FFS Patches */
          /** Prebuild patch */
          static SimplePatch* FFS_PermsCheck();

          /* DIP Patches */
          /** Prebuild patch */
          static SimplePatch* DIP_UnencryptedLimit();

          /** Prebuild patch */
          static SimplePatch* DIP_EnableDvdVideo();

          /* Other patches */
          /** Prebuild patch */
          static SimplePatch* KoreanKey_EnablePatch();

          /** Prebuild patch */
          static SimplePatch* getPatch(const std::string &s);

      };
    }
  }
}
#endif
