#include <libwiisys.h>

using namespace Libwiisys;
using namespace Libwiisys::Exceptions;
using namespace Libwiisys::Threading;

Thread::Thread(ThreadStart start) {
	_start = start;
}

void Thread::Start(Object* params) {
	_params = params; //record the parameters
	s32 code = LWP_CreateThread(&_threadId, Thread::EntryPoint, this, NULL, 0,
			70);
	if (code < 0)
		throw Exception("Error creating thread.", code);
}

void Thread::Run() {
	_start(_params);
}

void * Thread::EntryPoint(void * pthis) {
	Thread * pt = (Thread*) pthis;
	pt->Run();
	return NULL;
}

std::string Thread::GetType()
{
	return "Libwiisys::Threading::Thread,"+Object::GetType();
}
