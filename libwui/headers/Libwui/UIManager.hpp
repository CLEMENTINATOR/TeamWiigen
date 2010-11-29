#ifndef _UI_UIMANAGER_
#define _UI_UIMANAGER_

#include <gctypes.h>
#include "FreeTypeGX.h"

#include <Libwiisys/Object.h>

#include "Message.hpp"
#include "Component/Form.hpp"
#include "Component/Button.hpp"
#include "Device/Trigger.h"

extern FreeTypeGX *fontSystem[];

namespace Libwui
{
  class UIManager : public Libwiisys::Object
  {
    public:
      static void AddMessage(Message* message);
      static bool IsUiThread();
      static void Run(Libwui::Component::Form& main);
      static void ShowDialog(Libwui::Component::Form& dialog);
			static void TrackWPads(bool track);
			static void SetTrigger(Libwui::Component::Button& item, u32 flags);
      ~UIManager();
			
    private:
      std::queue<Message*> _messageQueue;
      std::vector<Libwui::Component::Form*> _dialogs;
			std::vector<Libwui::Device::Trigger> _triggers;
			
      mutex_t _messageQueueMutex;
      lwp_t _uiThread;
      bool _uiThreadDefined;
      Libwui::Component::Form* _rootElement;
      u32 _untilNextCacheClean;

      UIManager();
      void Update();
      static UIManager& Current();
  };
}

#endif
