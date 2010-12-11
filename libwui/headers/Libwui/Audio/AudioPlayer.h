#ifndef _AUDIO_PLAYER_H_
#define _AUDIO_PLAYER_H_

#include "../Control.hpp"
#include "ISongPlayer.h"

namespace Libwui
{
  namespace Audio
  {
  
	typedef enum
	{
		aprm_None,
		aprm_Repeat,
		aprm_RepeatAll,
	} AudioPlayerRepeatMode;
	
	class AudioPlayer : public Control
	{
	private:
		AudioPlayerRepeatMode _repeat;
		bool _random;
		
		std::vector<std::string> _trackList;
		std::string _uniqueTrackTitle;
		s32 _currentSong;
		bool _goNext;
		ISongPlayer* _player;
		
		std::vector<std::string> _randomList;
		
		AudioPlayer();		
		void EndOfSong(Libwiisys::Object* sender, Libwiisys::EventArgs*);
		void CreateRandomList();
		
	protected:
		void Draw();
		
	public:
		static AudioPlayer& Instance();
		void Play(const std::string& fileName);
		void PlayTrackList();
		void ClearTrackList();
		void Stop();
		void Reset();
		void AddTrack(const std::string& track);
		std::string GetCurrent();
		std::string GetNext();
		std::string GetPrevious();
		void RepeatMode(AudioPlayerRepeatMode mode);
		AudioPlayerRepeatMode GetRepeatMode();
		void IsRandom(bool random);
		bool IsRandom();
	};
  }
}

#endif
