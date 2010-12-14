#ifndef _AUDIO_PLAYER_H_
#define _AUDIO_PLAYER_H_

#include "../Control.hpp"
#include "../Audio/SAudioPlayer.h"

namespace Libwui
{
  namespace Component
  {
    class AudioPlayer : public Control
    {
      private:
        Libwui::Audio::SAudioPlayer *_playerInstance;

      public:
        AudioPlayer();
				~AudioPlayer();
        void Play(const std::string& fileName);
        void PlayTrackList();
        void ClearTrackList();
        void Stop();
        void Next();
        void Previous();
        void Pause();
        void Resume();
        void AddTrack(const std::string& track);
        std::string GetCurrent();
        std::string GetNext();
        std::string GetPrevious();
        void RepeatMode(Libwui::Audio::AudioPlayerRepeatMode mode);
        Libwui::Audio::AudioPlayerRepeatMode GetRepeatMode();
        void IsRandom(bool random);
        bool IsRandom();
				
				void InitializeComponents();
    };
  }
}

#endif
