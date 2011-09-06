#include <Libwui/Component/BackgroundWorker.h>
#include <Libwui/UIManager.hpp>
#include <Libwiisys/Exceptions/Exception.h>
#include <Libwiisys/threading/ThreadResult.h>
#include <FastDelegate.h>
#include <string>

using namespace std;
using namespace fastdelegate;
using namespace Libwiisys;
using namespace Libwiisys::Exceptions;
using namespace Libwiisys::Threading;
using namespace Libwui::Component;

BackgroundWorker::BackgroundWorker()
    : _thread(MakeDelegate(this, &BackgroundWorker::AsyncJob))
{
	_thread.ThreadTerminated += MakeDelegate(this,&BackgroundWorker::JobDone);
	r = NULL;
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

void BackgroundWorker::ProcessMessage(Message& message)
{
  if(message.GetComponentId() != _fullId)
  {
    Control::ProcessMessage(message);
    return;
  }

  string tag = message.GetTag();

  if(tag == "JobDone")
  {
    JobDone(0,r);
  }
	else
    Control::ProcessMessage(message);
}

void BackgroundWorker::JobDone(Object* sender, ThreadResultEventArgs* args)
{
	if(InvokeRequired())
	{
		if(r)
			delete r;
		r = new ThreadResultEventArgs(*args);
		Message* m = new Message(_fullId, "JobDone", "");
		UIManager::AddMessage(m);
		return;
	}
	WorkDone(this,args);
}

void BackgroundWorker::Draw()
{}


BackgroundWorker::~BackgroundWorker()
{
	if(r)
		delete r;
}