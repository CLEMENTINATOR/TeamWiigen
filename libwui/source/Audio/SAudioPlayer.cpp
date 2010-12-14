#include <Libwui/Audio/SAudioPlayer.h>
#include <Libwui/Audio/PlayerFactory.h>
#include <Libwui/UIManager.hpp>
#include <FastDelegate.h>
#include <unistd.h>
#include <cstdlib>
#include <sstream>

using namespace std;
using namespace fastdelegate;
using namespace Libwui;
using namespace Libwui::Audio;
using namespace Libwiisys;

SAudioPlayer::SAudioPlayer()
    : _repeat(aprm_None),
    _random(false),
    _currentSong(0),
    _player(NULL)
{}

void SAudioPlayer::EndOfSong(Object* sender, EventArgs* args)
{
  Next();
}

SAudioPlayer& SAudioPlayer::Instance()
{
  static SAudioPlayer p;
  return p;
}

void SAudioPlayer::ProcessMessage(Message& message)
{
  if(message.GetComponentId() != _fullId)
  {
    Control::ProcessMessage(message);
    return;
  }

  string tag = message.GetTag();
  stringstream params(message.GetSerializedParameters());

  if(tag == "Play")
    Play(params.str());
  else if(tag == "PlayTrackList")
    PlayTrackList();
  else if(tag == "Stop")
		Stop();
  else if(tag == "AddTrack")
		AddTrack(params.str());
	else if(tag == "Pause")
		Pause();
	else if(tag == "Resume")
		Resume();
	else if(tag == "RepeatMode")
	{
		s32 mode;
		params >> mode;
		RepeatMode((AudioPlayerRepeatMode)mode);
	}
	else if(tag == "IsRandom")
	{
		bool rnd;
		params >> rnd;
		IsRandom(rnd);		
	}
	else if(tag == "Next")
		Next();
	else if(tag == "Previous")
		Resume();
	else if(tag == "ClearTrackList")
		ClearTrackList();
  else
    Control::ProcessMessage(message);
}

void SAudioPlayer::Play(const std::string& fileName)
{
	if(InvokeRequired())
  {
    Message* m = new Message(_fullId, "Play", fileName);
    UIManager::AddMessage(m);
    return;
  }
	
  Stop();
  _trackList.clear();
  _randomList.clear();

  _trackList.push_back(fileName);
  Play();
}

void SAudioPlayer::PlayTrackList()
{
	if(InvokeRequired())
  {
    Message* m = new Message(_fullId, "PlayTrackList", "");
    UIManager::AddMessage(m);
    return;
  }
	
  Stop();
  Play();
}

void SAudioPlayer::Stop()
{
	if(InvokeRequired())
  {
    Message* m = new Message(_fullId, "Stop", "");
    UIManager::AddMessage(m);
    return;
  }
	
  if(_player)
  {
    _player->Stop();
    _player->PlayEnded -= MakeDelegate(this,&SAudioPlayer::EndOfSong);
    delete _player;
    _player = NULL;
  }

  _currentSong = 0;
}

void SAudioPlayer::AddTrack(const string& track)
{
	if(InvokeRequired())
  {
    Message* m = new Message(_fullId, "AddTrack", track);
    UIManager::AddMessage(m);
    return;
  }
	
  _trackList.push_back(track);
}

string SAudioPlayer::GetCurrent()
{
  if(_player)
    return _trackList[_currentSong];
  else
    return "";
}

void SAudioPlayer::Pause()
{
	if(InvokeRequired())
  {
    Message* m = new Message(_fullId, "Pause", "");
    UIManager::AddMessage(m);
    return;
  }
	
  if(_player)
  {
    _player->Pause();
  }
}

void SAudioPlayer::Resume()
{
	if(InvokeRequired())
  {
    Message* m = new Message(_fullId, "Resume", "");
    UIManager::AddMessage(m);
    return;
  }
	
  if(_player)
  {
    _player->Resume();
  }
}

string SAudioPlayer::GetNext()
{
  if(_random)
  {
    if((u32)(_currentSong + 1) < _randomList.size())
      return _randomList[_currentSong + 1];
  }
  else
  {
    if((u32)(_currentSong + 1) < _trackList.size())
      return _trackList[_currentSong + 1];
  }

  return "";
}

string SAudioPlayer::GetPrevious()
{
  if(_currentSong == 0)
    return "";

  if(_random)
    return _randomList[_currentSong - 1];
  else
    return _trackList[_currentSong - 1];
}

void SAudioPlayer::RepeatMode(AudioPlayerRepeatMode mode)
{
	if(InvokeRequired())
  {
		stringstream arg;
		arg << (s32)mode;
    Message* m = new Message(_fullId, "RepeatMode", arg.str());
    UIManager::AddMessage(m);
    return;
  }
	
  _repeat = mode;
}

AudioPlayerRepeatMode SAudioPlayer::GetRepeatMode()
{
  return _repeat;
}

void SAudioPlayer::IsRandom(bool random)
{
	if(InvokeRequired())
  {
		stringstream arg;
		arg << random;
    Message* m = new Message(_fullId, "IsRandom", arg.str());
    UIManager::AddMessage(m);
    return;
  }
	
  _random = random;
}

bool SAudioPlayer::IsRandom()
{
  return _random;
}

void SAudioPlayer::Next()
{
	if(InvokeRequired())
  {
    Message* m = new Message(_fullId, "Next", "");
    UIManager::AddMessage(m);
    return;
  }
	
  u32 actualSong = _currentSong;
	Stop();
	vector<string>* actualList = _random ? &_randomList : &_trackList;

	//if repeatAll and we are at the end of the playlist
	if(_repeat == aprm_RepeatAll && (actualSong + 1) == actualList->size())
	{
		_randomList.clear();
		Play();
		return;
	}

	//if repeat one
	if(_repeat == aprm_Repeat)
	{
		_currentSong = actualSong;
		Play();
		return;
	}

	if((actualSong + 1) == actualList->size())
		return;

	_currentSong = actualSong + 1;
	Play();
}

void SAudioPlayer::Previous()
{
	if(InvokeRequired())
  {
    Message* m = new Message(_fullId, "Previous", "");
    UIManager::AddMessage(m);
    return;
  }
	
	u32 actualSong = _currentSong;
	Stop();
	vector<string>* actualList = _random ? &_randomList : &_trackList;
	
	if(actualSong == 0 || (actualSong + 1) >= actualList->size())
		return;
		
	_currentSong = actualSong - 1;
	
	Play();
}

void SAudioPlayer::CreateRandomList()
{
  _randomList.clear();
  srand(time(NULL));

  while(_trackList.size() != _randomList.size())
  {
    int index = (int)((double)rand() / ((double)RAND_MAX + 1) * (_trackList.size() - _randomList.size()));
    for(vector<string>::iterator tr = _trackList.begin(); tr != _trackList.end(); tr++)
    {
      bool found = false;
      for(vector<string>::iterator ra = _randomList.begin(); ra != _randomList.end(); ra++)
      {
        if(*tr == *ra)
        {
          found = true;
          break;
        }
      }

      if(!found && index > 0)
        index--;
      else if(!found)
      {
        _randomList.push_back(*tr);
        break;
      }
    }
  }
}

void SAudioPlayer::ClearTrackList()
{
	if(InvokeRequired())
  {
    Message* m = new Message(_fullId, "ClearTrackList", "");
    UIManager::AddMessage(m);
    return;
  }
	
  Stop();
  _trackList.clear();
  _randomList.clear();
}

void SAudioPlayer::Play()
{
  if(_randomList.size() == 0)
    CreateRandomList();

  if(_random)
    _player = &PlayerFactory::GetPlayer(_randomList[_currentSong]);
  else
    _player = &PlayerFactory::GetPlayer(_trackList[_currentSong]);

  _player->PlayEnded += MakeDelegate(this,&SAudioPlayer::EndOfSong);
  _player->Play();
}
