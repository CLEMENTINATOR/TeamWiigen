#include <Libwui/Audio/ISongPlayer.h>

using namespace Libwiisys;
using namespace Libwui::Audio;

void ISongPlayer::OnPlayEnded(EventArgs& args)
{
	PlayEnded(this, &args);
}

void ISongPlayer::Play()
{}

void ISongPlayer::Stop()
{}

void ISongPlayer::Pause()
{}

void ISongPlayer::Resume()
{}
