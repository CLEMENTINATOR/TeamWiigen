#include <libwiisys/threading/BackgroundWorker.h>
#include <libwiisys/Exceptions/Exception.h>
#include <FastDelegate.h>

using namespace fastdelegate;
using namespace Libwiisys;
using namespace Libwiisys::Exceptions;
using namespace Libwiisys::Threading;

BackgroundWorker::BackgroundWorker()
    : _thread(MakeDelegate(this, &BackgroundWorker::AsyncJob))
{
	_thread.ThreadTerminated+=MakeDelegate(this,&BackgroundWorker::JobDone);
}

void BackgroundWorker::ReportProgress(f32 progress, std::string s)
{
  ProgressEventArgs e;
  e.percent = progress;
  e.message = s;
  ProgressChanged((Object*) this, &e);
}

void BackgroundWorker::RunWorkerAsync(Object *param)
{
  _thread.Start(param);
}

void* BackgroundWorker::AsyncJob(Object *param)
{
  DoWork(this, param);
  return NULL;
}
void BackgroundWorker::JobDone(Object* sender, ThreadResultEventArgs* args)
{
	WorkDone(this,args);
}
