#ifndef INSTALLERFACTORY_H_
#define INSTALLERFACTORY_H_

#include "Installer.h"
#include <Libwiisys/Object.h>
#include <Libwiisys/system/Patching/SimplePatch.h>
#include <Libwiisys/Shell/elf_abi.h>
#include <vector>
#include <Libwiisys/Serialization/Xml.h>

class InstallerFactory : public Libwiisys::Object
{
  public:
    static Installer* Create(TiXmlElement* node);
    static Installer* CreateCios(TiXmlElement* node);
    static void FillCiosPatches(Installer* cios, TiXmlElement* xml);
    static void FillCiosModules(Installer* cios, TiXmlElement* xml);
    static void FillCompositeInstaller(Installer* composite, TiXmlElement* node);
};

#endif /* INSTALLERFACTORY_H_ */
