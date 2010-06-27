#include <libwiisys.h>

using namespace Libwiisys;
using namespace Libwiisys::Exceptions;
using namespace Libwiisys::Threading;
/**
 *\brief Constructor
 */
Thread::Thread(ThreadStart start)
{
	_start = start;
}
/*
 * \brief Start the thread
 * \param params the parameterswhich are given to the thread
 */
void Thread::Start(Object* params)
{
   _params = params; //record the parameters
   s32 code = LWP_CreateThread(&_threadId, Thread::EntryPoint, this, NULL, 0, 70);
   if(code < 0)
     throw Exception("Error creating thread.", code);
}
/**
 *\brief Run the thread
 */
void Thread::Run()
{
   _start(_params);
}

/*static */
void * Thread::EntryPoint(void * pthis)
{
   Thread * pt = (Thread*)pthis;
   pt->Run();
   return NULL;
}
