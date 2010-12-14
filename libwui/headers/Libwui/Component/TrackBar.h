
#ifndef TRACKBAR_H_
#define TRACKBAR_H_
#include "Button.hpp"
#include <string>
#include <Libwiisys/Event.h>
#include "../Control.hpp"
namespace Libwui
{

  namespace Component
  {
    typedef enum
    {
      VerticalScroll,
      HorizontalScroll
    }
    ScrollOrientation;

    class TrackBar : public Control
    {
      public:
        TrackBar();
        virtual ~TrackBar();
        void InitializeComponents();
        void ProcessMessage(Message& message);

        void SetDefaultPreviousButtonImage(const std::string& img);
        void SetOverPreviousButtonImage(const std::string& img);
        void SetClickedPreviousButtonImage(const std::string& img);

        void SetDefaultNextButtonImage(const std::string& img);
        void SetOverNextButtonImage(const std::string& img);
        void SetClickedNextButtonImage(const std::string& img);

        void SetDefaultScroolBallImage(const std::string& img);
        void SetOverScroolBallImage(const std::string& img);
        void SetClickedScroolBallImage(const std::string& img);

        void SetDefaultScroolBarImage(const std::string& img);
        void SetOverScroolBarImage(const std::string& img);
        void SetClickedScroolBarImage(const std::string& img);

        void SetMaxValue(u32 val);
        void SetMinValue(u32 val);
        void SetIncrementalValue(u32 val);
        void SetBarOrientation(ScrollOrientation o);
        u32 GetValue();
        Libwiisys::Event ValueChanged;

      private :
        bool ScroolBallDraged;
        u32 ScroolBallDragedOffset;
        u32 MaxValue;
        u32 MinValue;
        u32 Value;
        u32 IncrementalValue;
        ScrollOrientation BarOrientation;
        Button PreviousButton;
        Button NextButton;
        Button ScroolBallButton;
        Button ScroolBarButton;

        void OnNextButtonClicked(Object* sender, Libwui::Events::CursorEventArgs* args);
        void OnPreviousButtonClicked(Object* sender, Libwui::Events::CursorEventArgs* args);
        void OnScroolBallMoved(Object* sender, Libwui::Events::CursorEventArgs* args);
        void OnScroolBallHold(Object* sender, Libwui::Events::CursorEventArgs* args);
        void OnScroolBallReleased(Object* sender, Libwui::Events::CursorEventArgs* args);

    };

  }

}


#endif /* TRACKBAR_H_ */
