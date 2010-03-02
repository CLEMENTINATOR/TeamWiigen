/*
 * InstallerFactory.h
 *
 *  Created on: 15 févr. 2010
 *      Author: julien
 */

#ifndef INSTALLERFACTORY_H_
#define INSTALLERFACTORY_H_

#include "Installer.h"
#include <libutils/Object.h>
#include <tinyxml.h>

class InstallerFactory : public Object
{
public:
	static Installer* Create(TiXmlElement* node);
	static Installer* CreateCios(TiXmlElement* node);
};

#endif /* INSTALLERFACTORY_H_ */
