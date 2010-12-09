#include <Sciifii/ui/graphic/GAudioPlayer.h>
#include <Libwui/Resources/Colors.h>
#include <Libwiisys/IO/File.h>
#include <Libwiisys/IO/Directory.h>
#include <Libwiisys/IO/Path.h>
#include <Libwui/Audio/AudioPlayer.h>


using namespace Libwui::Resources;
using namespace Libwui::Events;
using namespace Libwiisys::IO;
using namespace Libwui::Audio;
using namespace fastdelegate;

GAudioPlayer::GAudioPlayer():
    lblTitle(" ", 12, Colors::Black())
{
  _playing=false;
}
void GAudioPlayer::InitializeComponents()
{

  lblTitle.SetSize(100,22);
  lblTitle.SetPosition(0,0);
  lblTitle.Text("Press play!");
  bPlay.DefaultImage("playbutton_normal.png");
  bPlay.OverImage("playbutton_over.png");
  bPlay.SetSize(24, 24);
  bPlay.SetPosition(0,23);
  bPlay.Click+=MakeDelegate(this,&GAudioPlayer::Play);

  bStop.DefaultImage("stopbutton_normal.png");
  bStop.OverImage("stopbutton_over.png");
  bStop.SetSize(24, 24);
  bStop.SetPosition(25,23);
  bStop.Click+=MakeDelegate(this,&GAudioPlayer::Stop);

  bPrevious.DefaultImage("prevbutton_normal.png");
  bPrevious.OverImage("prevbutton_over.png");
  bPrevious.SetSize(24, 24);
  bPrevious.SetPosition(51,23);
  bPrevious.Click+=MakeDelegate(this,&GAudioPlayer::Previous);

  bNext.DefaultImage("nextbutton_normal.png");
  bNext.OverImage("nextbutton_over.png");
  bNext.SetSize(24,24);
  bNext.SetPosition(77,23);
  bNext.Click+=MakeDelegate(this,&GAudioPlayer::Next);

  AddChildren(&bPlay);
  AddChildren(&bStop);
  AddChildren(&bPrevious);
  AddChildren(&bNext);
  AddChildren(&lblTitle);

  Control::InitializeComponents();

}


void GAudioPlayer::SetTracklistFolder(const std::string& folder)
{
  AudioPlayer& a=AudioPlayer::Instance();
  a.ClearTrackList();
  std::vector<std::string> list=Directory::GetFiles(folder);
  for(u32 i =0;i<list.size();i++)
  {
    if(Path::GetFileExtension(list[i])=="mp3")
    {
      a.AddTrack(list[i]);
    }
  }
}


void GAudioPlayer::Play(Object*sender,CursorEventArgs* args)
{
  AudioPlayer& a=AudioPlayer::Instance();
  if(_playing) // pause
  {
    a.Pause();
    _playing=false;
    bPlay.DefaultImage("playbutton_normal.png");
    bPlay.OverImage("playbutton_over.png");
  }
  else
  {
    a.PlayTrackList();
    lblTitle.Text(Path::GetFileNameWithoutExtension(a.GetCurrent()));
    bPlay.DefaultImage("pausebutton_normal.png");
    bPlay.OverImage("pausebutton_over.png");
    _playing=true;
  }
}

void GAudioPlayer::Stop(Object*sender,CursorEventArgs* args)
{
  AudioPlayer& a=AudioPlayer::Instance();

  if(_playing) // pause
  {
    lblTitle.Text("");
    a.Stop();
    _playing=false;
    bPlay.DefaultImage("playbutton_normal.png");
    bPlay.OverImage("playbutton_over.png");
  }
}


void GAudioPlayer::Previous(Object*sender,CursorEventArgs* args)
{}

void GAudioPlayer::Next(Object*sender,CursorEventArgs* args)
{}
