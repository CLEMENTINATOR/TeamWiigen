
#include <Libwui/Audio/AudioPlayer.h>
#include <Libwui/Control.hpp>
#include <Libwui/Component/Button.hpp>
#include <Libwui/Component/Label.hpp>

class GAudioPlayer : public Libwui::Control
{
  public :
    GAudioPlayer();
    void InitializeComponents();
    void SetTracklistFolder(const std::string& folder);


  private:
    bool _playing;
    Libwui::Component::Button bPlay;
    Libwui::Component::Button bStop;
    Libwui::Component::Button bPrevious;
    Libwui::Component::Button bNext;
    Libwui::Component::Label lblTitle;
    void Play(Object*sender,Libwui::Events::CursorEventArgs* args);
    void Previous(Object*sender,Libwui::Events::CursorEventArgs* args);
    void Next(Object*sender,Libwui::Events::CursorEventArgs* args);
    void Stop(Object*sender,Libwui::Events::CursorEventArgs* args);
};
