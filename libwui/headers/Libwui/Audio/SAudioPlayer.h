#ifndef _SAUDIO_PLAYER_H_
#define _SAUDIO_PLAYER_H_

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

    class SAudioPlayer : public Control
    {
      private:
        std::vector<std::string> _trackList;
        std::vector<std::string> _randomList;

        AudioPlayerRepeatMode _repeat;
        bool _singleMode;
        bool _random;
        s32 _currentSong;
        ISongPlayer* _player;

        SAudioPlayer();
        void EndOfSong(Libwiisys::Object* sender, Libwiisys::EventArgs*);
        void CreateRandomList();
        void Play();

      public:
        static SAudioPlayer& Instance();
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
        void RepeatMode(AudioPlayerRepeatMode mode);
        AudioPlayerRepeatMode GetRepeatMode();
        void IsRandom(bool random);
        bool IsRandom();
				
				void ProcessMessage(Message& message);
    };
  }
}

#endif
