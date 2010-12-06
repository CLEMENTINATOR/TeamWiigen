#ifndef _I_SONG_PLAYER_H_
#define _I_SONG_PLAYER_H_

#include <Libwiisys/Object.h>
#include <Libwiisys/Event.h>

namespace Libwui
{
	namespace Audio
	{
		class ISongPlayer : public Libwiisys::Object
		{
		protected:
			void OnPlayEnded(Libwiisys::EventArgs& args);
			
		public:
			virtual void Play() = 0;
			virtual void Stop() = 0;
			virtual void Pause() = 0;
			virtual void Resume() = 0;
			
			Libwiisys::Event PlayEnded;
		};
	}
}

#endif