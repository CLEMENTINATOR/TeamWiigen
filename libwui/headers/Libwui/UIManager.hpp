#ifndef _UI_UIMANAGER_
#define _UI_UIMANAGER_

#include <queue>
#include <gctypes.h>
#include "FreeTypeGX.h"

#include <libwiisys.h>

#include "Message.hpp"
#include "Component/Form.hpp"

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
      ~UIManager();
			
    private:
      std::queue<Message*> _messageQueue;
      mutex_t _messageQueueMutex;
      lwp_t _uiThread;
      bool _uiThreadDefined;
      Libwui::Component::Form* _rootElement;
      Libwui::Component::Form* _modalDialog;

      UIManager();
      void Update();
      static UIManager& Current();
  };
}

#endif
