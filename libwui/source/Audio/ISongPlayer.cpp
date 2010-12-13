#include <Libwui/Audio/ISongPlayer.h>

using namespace Libwiisys;
using namespace Libwui::Audio;

void ISongPlayer::OnPlayEnded(EventArgs& args)
{
	PlayEnded(this, &args);
}

void ISongPlayer::Play()
{}

void* ISongPlayer::Play(void* iSongPlayer)
{
	((ISongPlayer*)iSongPlayer)->AsyncPlayer();
	return NULL;
}

void ISongPlayer::Stop()
{}

void ISongPlayer::Pause()
{}

void ISongPlayer::Resume()
{}

void ISongPlayer::SetVolume(u32 volume)
{
	if(volume>255) volume = 255;

	_volume = volume;
#ifdef __SNDLIB_H__
	SND_ChangeVolumeVoice(0,volume,volume);
#endif
}
