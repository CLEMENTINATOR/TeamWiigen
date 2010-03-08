/*
 * InstallerFactory.h
 *
 *  Created on: 15 f�vr. 2010
 *      Author: julien
 */

#ifndef INSTALLERFACTORY_H_
#define INSTALLERFACTORY_H_

#include "Installer.h"
#include <libutils/Object.h>
#include <libutils/system/SimplePatch.h>
#include <tinyxml.h>
#include <vector>

class InstallerFactory : public Object
{
public:
	static Installer* Create(TiXmlElement* node);
	static Installer* CreateCios(TiXmlElement* node);
	static void FillCiosCorpModules(Installer* corp, TiXmlElement* xml);
	static void FillCiosCorpItems(Installer* corp, TiXmlElement* xml);
	static void FillCiosPlugins(Installer* cios, TiXmlElement* xml);
	static std::vector<SimplePatch> GetPluginHandles(TiXmlElement* xml);
	static void FillCiosPatches(Installer* cios, TiXmlElement* xml);
	static void FillCiosModules(Installer* cios, TiXmlElement* xml);
	static Installer* CreateSystemUpdater(TiXmlElement* node);
	static void FillCompositeInstaller(Installer* composite, TiXmlElement* node);
};

#endif /* INSTALLERFACTORY_H_ */
