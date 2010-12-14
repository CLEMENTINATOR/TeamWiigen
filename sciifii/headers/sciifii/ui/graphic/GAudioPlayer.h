#include <Libwui/Control.hpp>
#include <Libwui/Component/Button.hpp>
#include <Libwui/Component/Label.hpp>
#include <Libwui/Component/AudioPlayer.h>

class GAudioPlayer : public Libwui::Control
{
  public :
    GAudioPlayer();
    void InitializeComponents();
    void SetTracklistFolder(const std::string& folder);


  private:
    bool _playing;
		Libwui::Component::AudioPlayer player;
    Libwui::Component::Button bPlay;
    Libwui::Component::Button bResume;
    Libwui::Component::Button bPause;
    Libwui::Component::Button bStop;
    Libwui::Component::Button bPrevious;
    Libwui::Component::Button bNext;
    Libwui::Component::Label lblTitle;
    void Play(Object*sender,Libwui::Events::CursorEventArgs* args);
    void Previous(Object*sender,Libwui::Events::CursorEventArgs* args);
    void Next(Object*sender,Libwui::Events::CursorEventArgs* args);
    void Pause(Object*sender,Libwui::Events::CursorEventArgs* args);
    void Resume(Object*sender,Libwui::Events::CursorEventArgs* args);
    void Stop(Object*sender,Libwui::Events::CursorEventArgs* args);
    void Draw();
};
