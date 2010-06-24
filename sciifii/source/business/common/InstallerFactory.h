/*
 * InstallerFactory.h
 *
 *  Created on: 15 févr. 2010
 *      Author: julien
 */

#ifndef INSTALLERFACTORY_H_
#define INSTALLERFACTORY_H_

#include "Installer.h"
#include <libwiisys.h>


#include <vector>

class InstallerFactory : public Libwiisys::Object
{
public:
	static Installer* Create(TiXmlElement* node);
	static Installer* CreateCios(TiXmlElement* node);
	static void FillCiosCorpModules(Installer* corp, TiXmlElement* xml);
	static void FillCiosCorpItems(Installer* corp, TiXmlElement* xml);
	static void FillCiosPlugins(Installer* cios, TiXmlElement* xml);
	static std::vector<Libwiisys::System::Patching::SimplePatch> GetPluginHandles(TiXmlElement* xml);
	static bool GetPluginHeader(TiXmlElement* xml, Elf32_Phdr& header);
	static void FillCiosPatches(Installer* cios, TiXmlElement* xml);
	static void FillCiosModules(Installer* cios, TiXmlElement* xml);
	static Installer* CreateSystemUpdater(TiXmlElement* node);
	static void FillCompositeInstaller(Installer* composite, TiXmlElement* node);
};

#endif /* INSTALLERFACTORY_H_ */
