#include <Libwui/Audio/AudioPlayer.h>
#include <Libwui/Audio/PlayerFactory.h>
#include <FastDelegate.h>

using namespace std;
using namespace fastdelegate;
using namespace Libwui::Audio;
using namespace Libwiisys;

AudioPlayer::AudioPlayer()
  : _currentSong(-1),
    _goNext(false),
	_player(NULL)
{}
		
void AudioPlayer::EndOfSong(Object* sender, EventArgs* args)
{
	_goNext = true;
}

void AudioPlayer::Draw()
{
	if(_goNext)
	{
		_goNext = false;
		Stop();
		
		if(_currentSong < 0)			
			return;
		
		if(_currentSong + 1 >= (s32)_trackList.size())
			return;
		
		_currentSong++;
		_player = &PlayerFactory::GetPlayer(_trackList[_currentSong]);
		_player->PlayEnded += MakeDelegate(this,&AudioPlayer::EndOfSong);
		_player->Play();
	}
}

AudioPlayer& AudioPlayer::GetAndReset()
{
	static AudioPlayer p;
	p.ClearTrackList();
	return p;
}

void AudioPlayer::Play(const std::string& fileName)
{
  Stop();
  _currentSong = -1;
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
	_player = &PlayerFactory::GetPlayer(_trackList[_currentSong]);
	_player->PlayEnded += MakeDelegate(this,&AudioPlayer::EndOfSong);
	_player->Play();
}
void AudioPlayer::ClearTrackList()
{
	if(_currentSong > 0)
		Stop();
	_trackList.clear();
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