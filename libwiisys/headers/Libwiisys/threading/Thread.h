#ifndef _UTILS_THREAD_H_
#define _UTILS_THREAD_H_

#include <fastdelegate.h>
#include "../Object.h"
#include <ogcsys.h>

/*! \namespace Libwiisys::Threading
 * \brief Object oriented Thread system
 */
namespace Libwiisys {
namespace Threading{
/**
 * \class Thread
 * \brief Manage and create thread easily
 * 
 * This class is used for multithreading in your programs
 */
class Thread : public Object
{
public:
	/** Simple typedef for a more readable code :)*/ 
	typedef fastdelegate::FastDelegate1<Object *> ThreadStart;
	Thread(ThreadStart start);
	void Start(Object* params = NULL);

private:
	lwp_t _threadId;
	ThreadStart _start;
	Object* _params;

protected:
	void Run();
	static void * EntryPoint(void*);
};
}
}
#endif
