
#ifndef GSCIIFIILAUNCHEDDIALOG_H_
#define GSCIIFIILAUNCHEDDIALOG_H_

#include <Libwiisys/Object.h>
#include <Libwui/Component/Form.hpp>
#include <Libwui/Component/Button.hpp>
#include <Libwui/Component/TextAera.h>
#include <Libwui/Component/DropDownList.hpp>
#include <Libwui/Component/MessageBox.hpp>
#include <Libwui/Component/ProgressBar.h>
#include <Libwiisys/threading/Thread.h>
#include <sciifii/Config.h>

class GSciifiiLauncher : public Libwui::Component::Form
{
  public:
	GSciifiiLauncher();
    void InitializeComponents();
    bool Run();
    void LaunchProcess(Object *sender, Object *args);
    void SetValueActual(Libwiisys::Object *sender, Libwiisys::Threading::ProgressEventArgs *p);
    void SetValueGlobal(Libwiisys::Object *sender, Libwiisys::Threading::ProgressEventArgs *p);
    virtual void Draw();
    void Exit(Libwiisys::Object *sender, Libwui::Events::CursorEventArgs *p);
    virtual ~GSciifiiLauncher();

    void JobDone(Libwiisys::Object* sender, Libwiisys::Threading::ThreadResultEventArgs* args);
  private :
    bool Prepare();
    void Execute();
    Libwui::Component::ProgressBar pBarGlobal;
    Libwui::Component::ProgressBar pBarActual;
    Libwui::Component::Button bOk;
    Libwiisys::Threading::BackgroundWorker bw;

};


#endif /* GSCIIFIILAUNCHEDDIALOG_H_ */
