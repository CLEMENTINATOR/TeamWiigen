#ifndef GMENUITEMFACTORY_H_
#define GMENUITEMFACTORY_H_

#include "IMenuItem.h"

class GMenuItemFactory : public Libwiisys::Object
{
  public:
    static IMenuItem* CreateItem(TiXmlElement* node);
};

#endif /* GMENUITEMFACTORY_H_ */
