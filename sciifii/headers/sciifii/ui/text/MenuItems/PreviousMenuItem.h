/*
 * PreviousMenuItem.h
 *
 *  Created on: 7 oct. 2010
 *      Author: Clément
 */

#ifndef PREVIOUSMENUITEM_H_
#define PREVIOUSMENUITEM_H_

class PreviousMenuItem: public NavigationMenuItem
{
public:
	PreviousMenuItem(TiXmlElement* node);
	virtual void ButtonPressed(u32 button);
};


#endif /* PREVIOUSMENUITEM_H_ */
