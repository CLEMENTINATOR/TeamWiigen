/*
 * ListItem.h
 *
 *  Created on: 11 oct. 2010
 *      Author: Clément
 */
#include "ListItemData.h"
#ifndef LISTITEM_H_
#define LISTITEM_H_
namespace Libwui
{
	namespace Component
	{
		class ListItem : public Control
		{
		public :
			ListItem(ListItemData* data);
			void InitializeComponents();
			void OverBackgroundColor(GXColor c);
			void NormalBackgroundColor(GXColor color);

		private :
			ListItemData* _data;
			Label _lbl;
			GXColor _overBackgroundColor;
			GXColor _normalBackgroundColor;
			
		protected :
			void ProcessMessage(Message& message);
			virtual void OnCursorEnter();
			virtual void OnCursorLeave();
		};
	}
}
#endif /* LISTITEM_H_ */
