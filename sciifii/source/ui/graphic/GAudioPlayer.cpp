#include <sciifii/ui/graphic/GAudioPlayer.h>
#include <Libwui/Resources/Colors.h>
#include <Libwiisys/IO/File.h>
#include <Libwiisys/IO/Directory.h>
#include <Libwiisys/IO/Path.h>

using namespace Libwui::Resources;
using namespace Libwui::Events;
using namespace Libwiisys::IO;
using namespace Libwui::Audio;
using namespace fastdelegate;

GAudioPlayer::GAudioPlayer():
    _playing(false), lblTitle(" ", 12, Colors::Black())
{}

void GAudioPlayer::InitializeComponents()
{
  lblTitle.SetSize(100,22);
  lblTitle.SetPosition(0,0);

  bPlay.DefaultImage("playbutton_normal.png");
  bPlay.OverImage("playbutton_over.png");
  bPlay.SetSize(24, 24);
  bPlay.SetPosition(0,23);
  bPlay.Click+=MakeDelegate(this,&GAudioPlayer::Play);

  bPause.DefaultImage("pausebutton_normal.png");
  bPause.OverImage("pausebutton_over.png");
  bPause.SetSize(24, 24);
  bPause.SetPosition(0,23);
  bPause.Enabled(false);
  bPause.Visible(false);
  bPause.Click+=MakeDelegate(this,&GAudioPlayer::Pause);

  bResume.DefaultImage("playbutton_normal.png");
  bResume.OverImage("playbutton_over.png");
  bResume.SetSize(24, 24);
  bResume.SetPosition(0,23);
  bResume.Enabled(false);
  bResume.Visible(false);
  bResume.Click+=MakeDelegate(this,&GAudioPlayer::Resume);

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
  bNext.SetPosition(78,23);
  bNext.Click+=MakeDelegate(this,&GAudioPlayer::Next);

  AddChildren(&bPlay);
  AddChildren(&bPause);
  AddChildren(&bStop);
  AddChildren(&bPrevious);
  AddChildren(&bNext);
  AddChildren(&bResume);
  AddChildren(&lblTitle);
  AddChildren(&player);

  Control::InitializeComponents();

}


void GAudioPlayer::SetTracklistFolder(const std::string& folder)
{
  player.ClearTrackList();
  std::vector<std::string> list=Directory::GetFiles(folder);
  for(u32 i =0;i<list.size();i++)
    player.AddTrack(list[i]);
}


void GAudioPlayer::Play(Object*sender,CursorEventArgs* args)
{
  if(!_playing)
  {
    player.PlayTrackList();
    bPlay.Enabled(false);
    bPause.Enabled(true);
    bPlay.Visible(false);
    bPause.Visible(true);
    _playing=true;
  }
}

void GAudioPlayer::Previous(Object*sender,CursorEventArgs* args)
{
  if(_playing)
    player.Previous();
}


void GAudioPlayer::Draw()
{
  lblTitle.Text(Path::GetFileNameWithoutExtension(player.GetCurrent()));
  Control::Draw();
}

void GAudioPlayer::Next(Object*sender,CursorEventArgs* args)
{
  if(_playing)
    player.Next();
}

void GAudioPlayer::Pause(Object*sender,Libwui::Events::CursorEventArgs* args)
{
  player.Pause();
  bResume.Enabled(true);
  bPause.Enabled(false);
  bResume.Visible(true);
  bPause.Visible(false);
}



void GAudioPlayer::Stop(Object*sender,Libwui::Events::CursorEventArgs* args)
{
  if(_playing)
  {
    player.Stop();
    bPlay.Enabled(true);
    bPlay.Visible(true);
    bResume.Enabled(false);
    bPause.Enabled(false);
    bResume.Visible(false);
    bPause.Visible(false);
    _playing=false;
  }
}
void GAudioPlayer::Resume(Object*sender,Libwui::Events::CursorEventArgs* args)
{
  player.Resume();
  bPause.Enabled(true);
  bResume.Enabled(false);
  bPause.Visible(true);
  bResume.Visible(false);
}
