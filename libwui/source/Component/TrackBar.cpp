#include <Libwui/Component/TrackBar.h>
#include <Libwui/Control.hpp>
#include <Libwui/UIManager.hpp>
#include <sstream>

using namespace Libwui;
using namespace std;
using namespace fastdelegate;
namespace Libwui
{

  namespace Component
  {

    TrackBar::TrackBar()
    {
      ScroolBallDraged=false;
      ScroolBallDragedOffset=0;
      PreviousButton.Click += MakeDelegate(this, &TrackBar::OnPreviousButtonClicked);
      NextButton.Click += MakeDelegate(this, &TrackBar::OnNextButtonClicked);
      ScroolBallButton.CursorMove += MakeDelegate(this, &TrackBar::OnScroolBallMoved);
      ScroolBallButton.CursorButtonDown += MakeDelegate(this, &TrackBar::OnScroolBallHold);
      ScroolBallButton.CursorButtonUp += MakeDelegate(this, &TrackBar::OnScroolBallReleased);
    }

    u32 TrackBar::GetValue()
    {
      return Value;
    }
    void  TrackBar::ProcessMessage(Message& message)
    {
      if (message.GetComponentId() != _fullId)
      {
        Control::ProcessMessage(message);
        return;
      }

      string tag = message.GetTag();
      stringstream params(message.GetSerializedParameters());

      if (tag == "SetMaxValue")
      {
        u32 v;
        params >> v;
        SetMaxValue(v);
      }
      else if (tag == "SetMinValue")
      {
        u32 v;
        params >> v;
        SetMinValue(v);
      }
      else if (tag == "SetIncrementalValue")
      {
        u32 v;
        params >> v;
        SetIncrementalValue(v);
      }
      else if (tag == "SetBarOrientation")
      {
        u32 v;
        params >> v;
        SetBarOrientation((ScrollOrientation)v);
      }
      else
        Control::ProcessMessage(message);
    }
    void TrackBar::InitializeComponents()
    {
      /**
       * TODO Positionner le bordel
       */

      AddChildren(&PreviousButton);
      AddChildren(&NextButton);
      AddChildren(&ScroolBallButton);
      AddChildren(&ScroolBarButton);
      Control::InitializeComponents();
    }
    TrackBar::~TrackBar()
    {}


    void TrackBar::SetDefaultPreviousButtonImage(const std::string& img)
    {
      PreviousButton.DefaultImage(img);
    }
    void TrackBar::SetOverPreviousButtonImage(const std::string& img)
    {
      PreviousButton.OverImage(img);
    }
    void TrackBar::SetClickedPreviousButtonImage(const std::string& img)
    {
      PreviousButton.ClickedImage(img);
    }
    void TrackBar::SetDefaultNextButtonImage(const std::string& img)
    {
      NextButton.DefaultImage(img);
    }
    void TrackBar::SetOverNextButtonImage(const std::string& img)
    {
      NextButton.OverImage(img);
    }
    void TrackBar::SetClickedNextButtonImage(const std::string& img)
    {
      NextButton.ClickedImage(img);
    }
    void TrackBar::SetDefaultScroolBallImage(const std::string& img)
    {
      ScroolBallButton.DefaultImage(img);
    }
    void TrackBar::SetOverScroolBallImage(const std::string& img)
    {
      ScroolBallButton.OverImage(img);
    }
    void TrackBar::SetClickedScroolBallImage(const std::string& img)
    {
      ScroolBallButton.ClickedImage(img);
    }
    void TrackBar::SetDefaultScroolBarImage(const std::string& img)
    {
      ScroolBarButton.DefaultImage(img);
    }
    void TrackBar::SetOverScroolBarImage(const std::string& img)
    {
      ScroolBarButton.OverImage(img);
    }
    void TrackBar::SetClickedScroolBarImage(const std::string& img)
    {
      ScroolBarButton.ClickedImage(img);
    }


    void TrackBar::SetMaxValue(u32 val)
    {
      if(InvokeRequired())
      {
        stringstream buffer;
        buffer << (u32)val;
        Message* m = new Message(_fullId, "SetMaxValue", buffer.str());
        UIManager::AddMessage(m);
        return;
      }
      MaxValue=val;
    }
    void TrackBar::SetMinValue(u32 val)
    {
      if(InvokeRequired())
      {
        stringstream buffer;
        buffer << (u32)val;
        Message* m = new Message(_fullId, "SetMinValue", buffer.str());
        UIManager::AddMessage(m);
        return;
      }
      MinValue=val;
    }
    void TrackBar::SetIncrementalValue(u32 val)
    {
      if(InvokeRequired())
      {
        stringstream buffer;
        buffer << (u32)val;
        Message* m = new Message(_fullId, "SetIncrementalValue", buffer.str());
        UIManager::AddMessage(m);
        return;
      }
      IncrementalValue=val;
    }
    void TrackBar::SetBarOrientation(ScrollOrientation o)
    {
      if(InvokeRequired())
      {
        stringstream buffer;
        buffer << (u32)o;
        Message* m = new Message(_fullId, "SetBarOrientation", buffer.str());
        UIManager::AddMessage(m);
        return;
      }
      BarOrientation=o;
    }



    void TrackBar::OnNextButtonClicked(Object* sender, Libwui::Events::CursorEventArgs* args)
    {
      if(Value+IncrementalValue>MaxValue)
      {
        Value=MaxValue;
        NextButton.Enabled(false);
      }
      else
      {
        Value+=IncrementalValue;
        NextButton.Enabled(true);
      }
      ValueChanged(this,NULL);
      /**
       * TODO Move trackball
       */
    }

    void TrackBar::OnPreviousButtonClicked(Object* sender, Libwui::Events::CursorEventArgs* args)
    {
      if(Value-IncrementalValue<MinValue)
      {
        Value=MinValue;
        PreviousButton.Enabled(false);
      }
      else
      {
        Value-=IncrementalValue;
        PreviousButton.Enabled(true);
      }
      ValueChanged(this,NULL);
      /**
       * TODO Move trackball
       */
    }

    void TrackBar::OnScroolBallMoved(Object* sender, Libwui::Events::CursorEventArgs* args)
    {
      Device::PadController controller = args->Controller();

      if(controller.wpad.btns_h == 0)
        ScroolBallDraged = false;

      if(!ScroolBallDraged)
        return;

      if(ScroolBallDraged)
      {
        int topPosition = controller.wpad.ir.y - ScroolBallDragedOffset;
        int yPosition;

        /**
         * TODO STUFF
         */
      }
    }

    void TrackBar::OnScroolBallHold(Object* sender, Libwui::Events::CursorEventArgs* args)
    {
      ScroolBallDraged = true;
      ScroolBallDragedOffset = args->Controller().wpad.ir.y - ScroolBarButton.GetTop();
    }

    void TrackBar::OnScroolBallReleased(Object* sender, Libwui::Events::CursorEventArgs* args)
    {
      ScroolBallDraged = false;
    }



  }

}
