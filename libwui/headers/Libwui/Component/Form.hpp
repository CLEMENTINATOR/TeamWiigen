#ifndef _UI_COMPONENT_FORM_
#define _UI_COMPONENT_FORM_

#include "../Control.hpp"
#include "../Message.hpp"

namespace Libwui
{
	namespace Component
	{
		class Form : public Libwui::Control
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
