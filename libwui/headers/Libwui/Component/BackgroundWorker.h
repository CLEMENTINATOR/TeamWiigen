#ifndef BACKGROUNDWORKER_H_
#define BACKGROUNDWORKER_H_

#include <Libwiisys/threading/Thread.h>
#include <Libwiisys/threading/ProgressEvent.h>
#include <Libwiisys/threading/DoWorkEvent.h>
#include <Libwiisys/threading/ThreadResult.h>
#include "../Control.hpp"

namespace Libwui
{
  namespace Component
  {
    class BackgroundWorker: public Control
    {
      public:
        Libwiisys::Threading::ProgressEvent ProgressChanged;
        Libwiisys::Threading::DoWorkEvent DoWork;
        Libwiisys::Threading::ThreadResultEvent WorkDone;
        BackgroundWorker();
				void ProcessMessage(Message& message);
        void ReportProgress(f32 progress,std::string s);
        void RunWorkerAsync(Libwiisys::Object *params);
			protected:
				void Draw();
      private:
				Libwiisys::Threading::ThreadResultEventArgs* r;
        void JobDone(Libwiisys::Object* sender, Libwiisys::Threading::ThreadResultEventArgs* args);
        Libwiisys::Threading::Thread _thread;
        void* AsyncJob(Libwiisys::Object* param);
    };
  }
} // namespace Libwiisys


#endif /* BACKGROUNDWORKER_H_ */
