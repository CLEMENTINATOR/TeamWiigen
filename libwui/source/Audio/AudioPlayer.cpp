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
    : _repeat(aprm_None),
			_random(false),
			_currentSong(0),
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
}

AudioPlayer& AudioPlayer::Instance()
{
  static AudioPlayer p;
  return p;
}

void AudioPlayer::Play(const std::string& fileName)
{
	Stop();
	_trackList.clear();
	_randomList.clear();
	
	_trackList.push_back(fileName);
	Play();
}

void AudioPlayer::PlayTrackList()
{
	Stop();
	Play();
}

void AudioPlayer::Stop()
{
	if(_player)
  {
    _player->Stop();
    _player->PlayEnded -= MakeDelegate(this,&AudioPlayer::EndOfSong);
    delete _player;
    _player = NULL;
  }
	
	_currentSong = 0;
}

void AudioPlayer::AddTrack(const string& track)
{
	_trackList.push_back(track);
}

string AudioPlayer::GetCurrent()
{
	if(_player)
		return _trackList[_currentSong];
	else
		return "";
}

string AudioPlayer::GetNext()
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

string AudioPlayer::GetPrevious()
{
	if(_currentSong == 0)
		return "";
		
	if(_random)
		return _randomList[_currentSong - 1];
	else
		return _trackList[_currentSong - 1];
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

void AudioPlayer::Next()
{
  _goNext=true;
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

void AudioPlayer::ClearTrackList()
{
	Stop();
	_trackList.clear();
	_randomList.clear();
}

void AudioPlayer::Play()
{
	if(_randomList.size() == 0)
		CreateRandomList();
		
	if(_random)
		_player = &PlayerFactory::GetPlayer(_randomList[_currentSong]);
	else
		_player = &PlayerFactory::GetPlayer(_trackList[_currentSong]);
		
	_player->PlayEnded += MakeDelegate(this,&AudioPlayer::EndOfSong);
	_player->Play();
}