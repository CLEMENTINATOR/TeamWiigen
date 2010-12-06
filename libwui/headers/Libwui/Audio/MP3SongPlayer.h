#ifndef _MP3_SONG_PLAYER_H_
#define _MP3_SONG_PLAYER_H_

#include <mad.h>
#include <string>
#include <Libwiisys/Buffer.h>
#include "ISongPlayer.h"
#include "MP3/EQState.h"
#include "MP3/OutputBuffer.h"

namespace Libwui
{
	namespace Audio
	{
		class MP3SongPlayer : public ISongPlayer
		{
		private:
			Libwiisys::Buffer _data;
			u64 _nbLus;
			Libwiisys::Buffer _currentFrame;
			MP3::EQState _eqs[2];
			MP3::OutputBuffer _outputRing;
			u8 _outputBuffers[2][ADMA_BUFFERSIZE] ATTRIBUTE_ALIGN(32);
			u8 _outputIndex;
			bool _playing;
			bool _needToStop;
			bool _hasSample;
			
			lwpq_t _queue;
			
			struct mad_stream Stream;
			struct mad_frame Frame;
			struct mad_synth Synth;
			
			static MP3SongPlayer* _current;
			
			bool FeedData(bool& lastFrame);
			void AsyncPlayer();
			void Resample();
			s16 FixedToShort(mad_fixed_t fixed);
			u8* CurrentBuffer();
			
		public:
			MP3SongPlayer(const std::string& file);
			MP3SongPlayer(Libwiisys::Buffer& buffer);
			void Play();
			void Stop();
			void Pause();
			void Resume();
			void DataTransferCallback();
			
			static MP3SongPlayer& Current();
		};
	}
}

#endif