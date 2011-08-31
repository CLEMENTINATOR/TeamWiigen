#ifndef TITLEPATCHER_H_
#define TITLEPATCHER_H_

#include <list>

#include "../Title.h"
#include "Patch.h"
#include "TitleModule.h"

/**
 * \namespace Libwiisys::System::Patching
 * \brief Tools to patch ioses
 *
 * Here are all the tools used to play with ios modules
 */
namespace Libwiisys
{
  namespace System
  {
    namespace Patching
    {

      /**
       * \class TitlePatcher
       * \brief Class used to patch Title
       * \author Teton,Arasium,Fanta
       * \version 1.0
       *
       * This class is the class where you can install ios ( or Title)
       * and patch them providing patches(Simple patch/plugin patch/Module patch)
       */
      class TitlePatcher : public Title
      {
        private:
          std::list<const Patch*> _patchList;
          std::list<TitleModule> _moduleList;
		  Buffer _newBanner;

		  bool _hasNewBanner;
          bool _tmdDirty;
          bool _tikDirty;


          u64 _titleId;
          s32 _revision;
          bool _fakeSign;
          virtual void DecryptTitleKey(Buffer& b_tik);
          void InsertModule(TitleModule& module, Buffer& b_tmd);
        public:
          virtual std::string GetType();
          /**
           * @brief Constructor
           * @param titleId The title id of the title
           * @param revision The revision of the title
           */
          TitlePatcher(u64 titleId = 0, s32 revision = -1,bool fakeSign=true);
          virtual void OnTicketLoading(Event::TitleEventArgs &processControl);
          virtual void OnTmdLoading(Event::TitleEventArgs &processControl);
          virtual void OnContentLoading(Event::TitleEventArgs &processControl);
          virtual void OnTicketInstalling(Event::TitleEventArgs &processControl);
          virtual void OnTmdInstalling(Event::TitleEventArgs &processControl);

          /**
           * @brief Add a patch to the patch list which will be applied while isntalling
           * @param patch Patch to add
           */
          void AddPatch(const Patch* patch);

          /**
           * @brief Add a module to the module list which will be applied while isntalling
           * @param module  TitleModule to add
           */
          void AddModule(TitleModule module);
		  
		  void DefineNewBanner(const Buffer& newBanner);
      };

    }
  }
}
#endif
