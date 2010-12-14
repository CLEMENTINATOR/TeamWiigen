#include <Libwui/Component/AudioPlayer.h>

using namespace Libwui::Component;
using namespace Libwui::Audio;
using namespace std;

AudioPlayer::AudioPlayer()
  : _playerInstance(&SAudioPlayer::Instance())
{}

AudioPlayer::~AudioPlayer()
{
	RemoveChildren(_playerInstance);
}

void AudioPlayer::InitializeComponents()
{
	AddChildren(_playerInstance);
}

void AudioPlayer::Play(const string& fileName)
{
	_playerInstance->Play(fileName);
}

void AudioPlayer::PlayTrackList()
{
	_playerInstance->PlayTrackList();
}

void AudioPlayer::ClearTrackList()
{
	_playerInstance->ClearTrackList();
}

void AudioPlayer::Stop()
{
	_playerInstance->Stop();
}

void AudioPlayer::Next()
{
	_playerInstance->Next();
}

void AudioPlayer::Previous()
{
	_playerInstance->Previous();
}

void AudioPlayer::Pause()
{
	_playerInstance->Pause();
}

void AudioPlayer::Resume()
{
	_playerInstance->Resume();
}

void AudioPlayer::AddTrack(const std::string& track)
{
	_playerInstance->AddTrack(track);
}

string AudioPlayer::GetCurrent()
{
	return _playerInstance->GetCurrent();
}

string AudioPlayer::GetNext()
{
	return _playerInstance->GetNext();
}

string AudioPlayer::GetPrevious()
{
	return _playerInstance->GetPrevious();
}

void AudioPlayer::RepeatMode(AudioPlayerRepeatMode mode)
{
	_playerInstance->RepeatMode(mode);
}

Libwui::Audio::AudioPlayerRepeatMode AudioPlayer::GetRepeatMode()
{
	return _playerInstance->GetRepeatMode();
}

void AudioPlayer::IsRandom(bool random)
{
	_playerInstance->IsRandom(random);
}

bool AudioPlayer::IsRandom()
{
	return _playerInstance->IsRandom();
}
