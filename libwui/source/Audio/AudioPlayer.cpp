#include <Libwui/Audio/AudioPlayer.h>
#include <Libwui/Audio/PlayerFactory.h>
#include <FastDelegate.h>
#include <unistd.h>
#include <cstdlib>

using namespace std;
using namespace fastdelegate;
using namespace Libwui::Audio;
using namespace Libwiisys;

AudioPlayer::AudioPlayer()
    : _random(false),
    _currentSong(-1),
    _goNext(false),
    _player(NULL)
{}

void AudioPlayer::EndOfSong(Object* sender, EventArgs* args)
{
  usleep(1000);
  _goNext = true;
}

void AudioPlayer::Draw()
{
  if(_goNext)
  {
    _goNext = false;
    string uniqueTrack = _uniqueTrackTitle;
    //if repeat we play the same song again
    if(_repeat == aprm_Repeat || (_currentSong < 0 && _repeat == aprm_RepeatAll))
    {
      _player->Stop();
      //we restore the unique track title
      _uniqueTrackTitle = uniqueTrack;
      _player->Play();
      return;
    }

    Stop();

    //if this was a single song, we just stop
    if(_currentSong < 0)
      return;

    //if not repeat all, we left at the end of the playlist
    if(_repeat != aprm_RepeatAll)
    {
      if(!_random && _currentSong + 1 >= (s32)_trackList.size())
      {
        _currentSong = -1;
        return;
      }

      if(_random && _currentSong + 1 >= (s32)_randomList.size())
      {
        _currentSong = -1;
        return;
      }

      _currentSong++;
    }
    //if repeat all and we are at the end of the tracklist
    else
    {
      if(!_random && _currentSong + 1 >= (s32)_trackList.size())
        _currentSong = 0;
      else if(_random && _currentSong + 1 >= (s32)_randomList.size())
      {
        _currentSong = 0;
        CreateRandomList();
      }
      else
        _currentSong++;
    }

    if(!_random)
      _player = &PlayerFactory::GetPlayer(_trackList[_currentSong]);
    else
      _player = &PlayerFactory::GetPlayer(_randomList[_currentSong]);

    _player->PlayEnded += MakeDelegate(this,&AudioPlayer::EndOfSong);
    _player->Play();
  }
}

AudioPlayer& AudioPlayer::Instance()
{
  static AudioPlayer p;
  return p;
}

void AudioPlayer::Play(const std::string& fileName)
{
  Stop();
  _currentSong = -1;
  _uniqueTrackTitle = fileName;
  _player = &PlayerFactory::GetPlayer(fileName);
  _player->PlayEnded += MakeDelegate(this,&AudioPlayer::EndOfSong);
  _player->Play();
}

void AudioPlayer::PlayTrackList()
{
  Stop();
  if(_trackList.size() == 0)
    return;

  _currentSong = 0;

  if(_random)
  {
    CreateRandomList();
    _player = &PlayerFactory::GetPlayer(_randomList[_currentSong]);
  }
  else
  {
    _player = &PlayerFactory::GetPlayer(_trackList[_currentSong]);
  }
  _player->PlayEnded += MakeDelegate(this,&AudioPlayer::EndOfSong);
  _player->Play();
}

void AudioPlayer::ClearTrackList()
{
  Stop();
  _trackList.clear();
  _currentSong = -1;
}

void AudioPlayer::Stop()
{
  if(_player)
  {
    _uniqueTrackTitle = "";
    _player->Stop();
    _player->PlayEnded -= MakeDelegate(this,&AudioPlayer::EndOfSong);
    delete _player;
    _player = NULL;
  }
}

void AudioPlayer::Pause()
{
  if(_player)
    _player->Pause();
}

void AudioPlayer::Resume()
{
  if(_player)
    _player->Resume();
}

void AudioPlayer::Reset()
{
  Stop();
  ClearTrackList();
  _repeat = aprm_None;
  _random = false;
  _currentSong = 0;
}

void AudioPlayer::AddTrack(const string& track)
{
  _trackList.push_back(track);
}

string AudioPlayer::GetCurrent()
{
  if(_currentSong == -1)
    return _uniqueTrackTitle;
  else if(_random)
    return _randomList[_currentSong];

  return _trackList[_currentSong];
}

string AudioPlayer::GetNext()
{
  if(_currentSong == 0)
    return "";

  if(_random)
  {
    if((s32)_randomList.size() >= _currentSong + 1)
      return "";
    else
      return _randomList[_currentSong + 1];
  }
  else
  {
    if((s32)_trackList.size() >= _currentSong + 1)
      return "";
    else
      return _trackList[_currentSong + 1];
  }
}

string AudioPlayer::GetPrevious()
{
  if(_currentSong == 0)
    return "";

  if(_random && (s32)_randomList.size() >= _currentSong)
    return _randomList[_currentSong - 1];
  else if(!_random && (s32)_trackList.size() >= _currentSong)
    return _trackList[_currentSong - 1];

  return "";
}

void AudioPlayer::RepeatMode(AudioPlayerRepeatMode mode)
{
  _repeat = mode;
}

AudioPlayerRepeatMode AudioPlayer::GetRepeatMode()
{
  return _repeat;
}

void AudioPlayer::IsRandom(bool random)
{
  _random = random;
}

bool AudioPlayer::IsRandom()
{
  return _random;
}

void AudioPlayer::CreateRandomList()
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
