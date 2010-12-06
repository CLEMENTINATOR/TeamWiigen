#ifndef _MP3_SONG_PLAYER_H_
#define _MP3_SONG_PLAYER_H_

#include <string>
#include <Libwiisys/Buffer.h>
#include "ISongPlayer.h"

namespace Libwui
{
	namespace Audio
	{
		class MP3SongPlayer : public ISongPlayer
		{
		public:
			MP3SongPlayer(const std::string& file);
			MP3SongPlayer(Libwiisys::Buffer& buffer);
			void Play();
			void Stop();
			void Pause();
			void Resume();
		};
	}
}

#endif