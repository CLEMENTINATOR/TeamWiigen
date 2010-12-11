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

  bPlay.DefaultImage("playbutton_normal.png");
  bPlay.OverImage("playbutton_over.png");
  bPlay.SetSize(24, 24);
  bPlay.SetPosition(0,23);
  bPlay.Click+=MakeDelegate(this,&GAudioPlayer::Play);

  bPrevious.DefaultImage("prevbutton_normal.png");
  bPrevious.OverImage("prevbutton_over.png");
  bPrevious.SetSize(24, 24);
  bPrevious.SetPosition(25,23);
  bPrevious.Click+=MakeDelegate(this,&GAudioPlayer::Previous);

  bNext.DefaultImage("nextbutton_normal.png");
  bNext.OverImage("nextbutton_over.png");
  bNext.SetSize(24,24);
  bNext.SetPosition(51,23);
  bNext.Click+=MakeDelegate(this,&GAudioPlayer::Next);

  AddChildren(&bPlay);
  AddChildren(&bPrevious);
  AddChildren(&bNext);
  AddChildren(&lblTitle);
  AddChildren(&AudioPlayer::Instance());

  Control::InitializeComponents();

}


void GAudioPlayer::SetTracklistFolder(const std::string& folder)
{
  AudioPlayer& a=AudioPlayer::Instance();
  a.ClearTrackList();
  std::vector<std::string> list=Directory::GetFiles(folder);
  for(u32 i =0;i<list.size();i++)
    a.AddTrack(list[i]);
}


void GAudioPlayer::Play(Object*sender,CursorEventArgs* args)
{
  AudioPlayer& a=AudioPlayer::Instance();
  if(_playing) // pause
  {
    a.Stop();
    _playing=false;
    bPlay.DefaultImage("stopbutton_normal.png");
    bPlay.OverImage("stopbutton_over.png");
  }
  else
  {
    a.PlayTrackList();
    bPlay.DefaultImage("pausebutton_normal.png");
    bPlay.OverImage("pausebutton_over.png");
    _playing=true;
  }
}

void GAudioPlayer::Previous(Object*sender,CursorEventArgs* args)
{}


void GAudioPlayer::Draw()
{
  AudioPlayer& a=AudioPlayer::Instance();
  lblTitle.Text(Path::GetFileNameWithoutExtension(a.GetCurrent()));
  Control::Draw();
}
void GAudioPlayer::Next(Object*sender,CursorEventArgs* args)
{}
