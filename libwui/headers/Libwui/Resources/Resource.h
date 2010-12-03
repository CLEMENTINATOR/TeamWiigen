#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <Libwiisys/Object.h>

namespace Libwui
{
  namespace Resources
  {
	class Resource : public Libwiisys::Object
	{
	public:
		Resource();
		virtual ~Resource();
		virtual void Clean();
		bool isDefault;
	};
  }
}

#endif /* RESOURCE_H_ */
