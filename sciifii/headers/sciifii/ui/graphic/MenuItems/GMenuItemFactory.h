#ifndef GMENUITEMFACTORY_H_
#define GMENUITEMFACTORY_H_

#include "GMenuItem.h"

class GMenuItemFactory : public Libwiisys::Object
{
  public:
    static GMenuItem* CreateItem(TiXmlElement* node);
};

#endif /* GMENUITEMFACTORY_H_ */
