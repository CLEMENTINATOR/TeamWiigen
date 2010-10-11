#ifndef _LIST_H_
#define _LIST_H_

#include <vector>
#include <libwiisys.h>
#include "../Control.hpp"
#include "../Message.hpp"
#include "ListItem.h"
#include "ListItemData.h"

namespace Libwui
{
	namespace Component
	{
		class List : public Control
		{
		public :
			void AddItem(Libwiisys::Object* item,const std::string& text = "");

		private :
			std::vector<ListItemData> _dataItems;
			std::vector<ListItem*> _items;
			ListItem* _selectedItem;
			
			void SetSize(s32 w, s32 h);
			
		protected :
			void EnsureItems();
		};
	}
}
#endif