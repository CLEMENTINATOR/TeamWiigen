#ifndef _UI_UIMANAGER_
#define _UI_UIMANAGER_

#include <queue>
#include <gctypes.h>
#include "FreeTypeGX.h"

#include <libwiisys.h>

#include "Message.hpp"
#include "Component/Form.hpp"

extern FreeTypeGX *fontSystem[];

namespace UI
{
	class UIManager : public Libwiisys::Object
	{
	public:
		static void AddMessage(Message* message);
		static bool IsUiThread();
		static void Run(UI::Component::Form& main);
		~UIManager();
	private:
		std::queue<Message*> _messageQueue;
		mutex_t _messageQueueMutex;
		lwp_t _uiThread;
		bool _uiThreadDefined;
		UI::Component::Form* _rootElement;

		UIManager();
		void Update();
		static UIManager& Current();
	};
}

#endif
