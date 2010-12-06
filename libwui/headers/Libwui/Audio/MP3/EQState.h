#ifndef _MP3_EQSTATE_H_
#define _MP3_EQSTATE_H_

#include <gctypes.h>
#include <Libwiisys/Object.h>

namespace Libwui
{
	namespace Audio
	{
		namespace MP3
		{
			class EQState : public Libwiisys::Object
			{
			private:
				f32 lf;
				f32 f1p0;
				f32 f1p1;
				f32 f1p2;
				f32 f1p3;
				
				f32 hf;
				f32 f2p0;
				f32 f2p1;
				f32 f2p2;
				f32 f2p3;
				
				f32 sdm1;
				f32 sdm2;
				f32 sdm3;
				
				f32 lg;
				f32 mg;
				f32 hg;
				
			public:
				EQState(s32 lowfreq = 880, s32 highfreq = 5000, s32 mixfreq = 48000);
				s16 Do(s16 sample);
			};
		}
	}
}

#endif