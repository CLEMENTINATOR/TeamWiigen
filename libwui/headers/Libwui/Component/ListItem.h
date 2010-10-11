#ifndef LISTITEM_H_
#define LISTITEM_H_

#include "../Control.hpp"
#include "../Message.hpp"
#include "Label.hpp"
#include "ListItemData.h"

namespace Libwui
{
	namespace Component
	{
		class ListItem : public Control
		{
		public :
			ListItem(ListItemData data);
			void InitializeComponents();
			void OverBackgroundColor(GXColor c);
			void NormalBackgroundColor(GXColor color);

		private :
			ListItemData _data;
			Label _lbl;
			GXColor _overBackgroundColor;
			GXColor _normalBackgroundColor;
			
		protected :
			void Draw();
			void ProcessMessage(Message& message);
			virtual void OnCursorEnter();
			virtual void OnCursorLeave();
		};
	}
}
#endif /* LISTITEM_H_ */
