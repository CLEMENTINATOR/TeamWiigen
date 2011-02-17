
#ifndef GSCIIFIILAUNCHEDDIALOG2_H_
#define GSCIIFIILAUNCHEDDIALOG2_H_

#include <Libwiisys/Object.h>
#include <Libwui/Component/Form.hpp>
#include <Libwui/Component/Button.hpp>
#include <Libwui/Component/TextAera.h>
#include <Libwui/Component/DropDownList.hpp>
#include <Libwui/Component/MessageBox.hpp>
#include <Libwui/Component/ProgressBar.h>
#include <Libwui/Component/BackgroundWorker.h>
#include <sciifii/Config.h>

class GSciifiiLauncher2 : public Libwui::Component::Form
{
  public:

    void InitializeComponents();
    virtual void Draw();
    void Exit(Libwiisys::Object *sender, Libwui::Events::CursorEventArgs *p);

  private :
    bool Prepare();
    void Execute();
    void LaunchProcess();
    Libwui::Component::ProgressBar pBarGlobal;
    Libwui::Component::ProgressBar pBarActual;
    Libwui::Component::Button bOk;
    Libwui::Component::MessageBox mb;
    Libwui::Component::BackgroundWorker bw;
};


#endif /* GSCIIFIILAUNCHEDDIALOG_H_ */
