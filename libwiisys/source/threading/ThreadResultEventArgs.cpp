#include <libwiisys.h>

using namespace Libwiisys::Threading;

ThreadResultEventArgs::ThreadResultEventArgs(ThreadResult r, u32 tid)
{
	Result = r;
	ThreadId = tid;
}