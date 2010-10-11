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
			virtual ~ListItem();
			void OverBackgroundColor(GXColor c);
			void InitializeComponents();
			void BackgroundColor(GXColor color);
			void Text(std::string text);
		private :
			ListItemData* _data;
			Label _lbl;
			GXColor _overBackgroundColor;
			GXColor _normalBackgroundColor;
		protected :
			void ProcessMessage(Message& message);
			virtual void OnCursorEnter();
			virtual void OnCursorLeave();
			virtual void Draw();
			virtual void EnsureItems();


		};
	}
}
#endif /* LISTITEM_H_ */
