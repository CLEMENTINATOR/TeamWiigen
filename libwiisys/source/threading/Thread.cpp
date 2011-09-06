#include <Libwiisys/threading/Thread.h>
#include <Libwiisys/Exceptions/Exception.h>
#include <Libwiisys/Exceptions/SystemException.h>
#include <vector>
#include <map>

using namespace Libwiisys;
using namespace Libwiisys::Exceptions;
using namespace Libwiisys::Threading;
using namespace std;

static map<lwp_t, Thread*> _threadList;
static vector<Thread*> _threadToResume;

Thread::Thread(ThreadStart start)
{
  _start = start;
  _threadResult.HasError = false;
 _threadResult.e=NULL;
}

Thread::~Thread()
{
  if(_threadResult.e!=NULL)
    delete _threadResult.e;
}

void Thread::Start(Object* params)
{
  _params = params; //record the parameters
  s32 code = LWP_CreateThread(&_threadId, Thread::EntryPoint, this, NULL, 0, 40);
  
  if (code < 0)
    throw SystemException("Error creating thread.", code);

  _threadList[_threadId] = this;

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
  catch(Exception &e)
  {
    pt->_threadResult.HasError = true;
    pt->_threadResult.e=new Exception(e);
  }
  catch(...)
  {
    pt->_threadResult.HasError = true;
    pt->_threadResult.e= new Exception("Unhandled Exception !");
  }

  ThreadResultEventArgs args(pt->_threadResult, pt->_threadId);
  pt->ThreadTerminated(pt, &args);
  _threadList.erase(_threadList.find(pt->_threadId));
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

void Thread::SuspendOtherThreads()
{
	lwp_t currentThread = LWP_GetSelf();
	for(map<lwp_t, Thread*>::iterator ite = _threadList.begin(); ite != _threadList.end(); ite++)
	{
		if(ite->first != currentThread && !LWP_ThreadIsSuspended(ite->second->_threadId))
		{
			ite->second->Suspend();
			_threadToResume.push_back(ite->second);
		}
	}
}

void Thread::ResumeOtherThreads()
{
	for(vector<Thread*>::iterator ite = _threadToResume.begin(); ite != _threadToResume.end(); ite++)
		(*ite)->Resume();
		
	_threadToResume.clear();
}
