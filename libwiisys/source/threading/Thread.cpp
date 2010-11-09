#include <libwiisys/threading/Thread.h>
#include <libwiisys/Exceptions/Exception.h>
#include <libwiisys/Exceptions/SystemException.h>
#include <libwiisys/Logging/Log.h>

using namespace Libwiisys;
using namespace Libwiisys::Exceptions;
using namespace Libwiisys::Threading;
using namespace Libwiisys::Logging;
Thread::Thread(ThreadStart start)
{
  _start = start;
}

void Thread::Start(Object* params)
{
  _params = params; //record the parameters
  s32 code = LWP_CreateThread(&_threadId, Thread::EntryPoint, this, NULL, 0, 70);
  if (code < 0)
    throw SystemException("Error creating thread.", code);
}

void* Thread::Run()
{
  return _start(_params);
}

void * Thread::EntryPoint(void * pthis)
{
  Thread * pt = (Thread*) pthis;
  pt->_threadResult.HasError =false;
  try
  {
    pt->_threadResult.Result = pt->Run();
  }
  catch(...)
  {
    pt->_threadResult.HasError = true;
  }

  ThreadResultEventArgs args(pt->_threadResult, pt->_threadId);
  pt->ThreadTerminated(pt, &args);
  return NULL;
}

std::string Thread::GetType()
{
  return "Libwiisys::Threading::Thread,"+Object::GetType();
}

void Thread::Suspend()
{
  if(LWP_SuspendThread(_threadId) < 0)
    throw Exception("Cannot suspend the thread.");
}

void Thread::Resume()
{
  if(LWP_ResumeThread(_threadId) < 0)
    throw Exception("Canno't resume the thread");
}

void* Thread::Join()
{
  void* result;
  if(LWP_JoinThread  (_threadId, &result) < 0)
    throw Exception("Error joining the thread.");
  if(_threadResult.HasError)
    throw Exception("The subthread thrown an exception.");
  return _threadResult.Result;
}
