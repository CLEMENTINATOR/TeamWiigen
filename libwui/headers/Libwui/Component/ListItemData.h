/*
 * ListItemData.h
 *
 *  Created on: 11 oct. 2010
 *      Author: Clément
 */

#ifndef LISTITEMDATA_H_
#define LISTITEMDATA_H_

#include <string>
#include <libwiisys.h>
namespace Libwui
{
	namespace Component
	{
		typedef struct ListItemData
		{
			Libwiisys::Object *data;
			std::string text;
		} ListItemData;
	}
}
#endif /* LISTITEMDATA_H_ */
