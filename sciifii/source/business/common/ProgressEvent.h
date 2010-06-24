#ifndef PROGRESSEVENT_H_
#define PROGRESSEVENT_H_

#include <libwiisys.h>


#include "ProgressEventArgs.h"
#include <fastdelegate.h>
#include <list>

class ProgressEvent : public Libwiisys::Object
{
public:
	typedef fastdelegate::FastDelegate2<Object*,ProgressEventArgs*> DelegateType;
	virtual void operator()(Object* sender, ProgressEventArgs* args);
	virtual void operator+= (DelegateType listener);
	virtual void operator-= (DelegateType listener);
private:
	std::list<DelegateType> listenerList;  // pointer to object
};

#endif /* PROGRESSEVENT_H_ */
