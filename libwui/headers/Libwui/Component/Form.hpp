#ifndef _UI_COMPONENT_FORM_
#define _UI_COMPONENT_FORM_

#include "../Control.hpp"
#include "../Message.hpp"

namespace UI
{
	namespace Component
	{
		class Form : public UI::Control
		{			
		protected:
			bool IsInUITree();			
		public:
			void SetRoot(bool root);
			Form();
		private:
			bool isRoot;
		};
	}
}

#endif
