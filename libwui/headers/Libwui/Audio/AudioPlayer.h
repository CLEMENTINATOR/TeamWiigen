#ifndef _AUDIO_PLAYER_H_
#define _AUDIO_PLAYER_H_

#include "../Control.hpp"
#include "ISongPlayer.h"

namespace Libwui
{
  namespace Audio
  {
	class AudioPlayer : public Control
	{
	private:
		std::vector<std::string> _trackList;
		s32 _currentSong;
		bool _goNext;
		ISongPlayer* _player;
		
		AudioPlayer();		
		void EndOfSong(Libwiisys::Object* sender, Libwiisys::EventArgs*);
		
	protected:
		void Draw();
		
	public:
		static AudioPlayer& GetAndReset();
		void Play(const std::string& fileName);
		void PlayTrackList();
		void ClearTrackList();
		void Stop();
		void Pause();
		void Resume();
	};
  }
}

#endif