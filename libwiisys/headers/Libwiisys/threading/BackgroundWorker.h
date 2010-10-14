#ifndef BACKGROUNDWORKER_H_
#define BACKGROUNDWORKER_H_

#include "Thread.h"
#include "ProgressEvent.h"
#include "DoWorkEvent.h"

namespace Libwiisys
{
  namespace Threading
  {
    class BackgroundWorker: public Object
    {

      public:
        ProgressEvent ProgressChanged;
        DoWorkEvent DoWork;

        BackgroundWorker();
        void ReportProgress(f32 progress,std::string s);
        void RunWorkerAsync(Object *params);
      private:
        Thread _thread;
        void* AsyncJob(Object* param);
    };
  }
} // namespace Libwiisys


#endif /* BACKGROUNDWORKER_H_ */
