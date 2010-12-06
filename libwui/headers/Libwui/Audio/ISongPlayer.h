#ifndef _I_SONG_PLAYER_H_
#define _I_SONG_PLAYER_H_

#include <Libwiisys/Object.h>
#include <Libwiisys/Event.h>
#include <gctypes.h>

namespace Libwui
{
	namespace Audio
	{
		class ISongPlayer : public Libwiisys::Object
		{
		protected:
			void OnPlayEnded(Libwiisys::EventArgs& args);
			u32 _volume;
			
		public:
			virtual void Play() = 0;
			virtual void Stop() = 0;
			virtual void Pause() = 0;
			virtual void Resume() = 0;
			void SetVolume(u32 volume);
			
			Libwiisys::Event PlayEnded;
		};
	}
}

#endif