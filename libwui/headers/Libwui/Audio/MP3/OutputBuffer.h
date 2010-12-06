#ifndef _MP3_OUTPUT_BUFFER_H_
#define _MP3_OUTPUT_BUFFER_H_

#include <Libwiisys/Object.h>

#ifndef __SNDLIB_H__
	#define ADMA_BUFFERSIZE			(4992)
#else
	#define ADMA_BUFFERSIZE			(8192)
#endif

#define DATABUFFER_SIZE			(32768)

namespace Libwui
{
	namespace Audio
	{
		namespace MP3
		{
			class OutputBuffer : public Libwiisys::Object
			{
			private:
				void* bs;
				u32* put;
				u32* get;
				bool buf_filled;
				u8 buffer[DATABUFFER_SIZE];
			public:
				OutputBuffer();
				s32 Used();
				s32 Space();
				s32 Get(void* data, s32 len);
				bool Put(void* data, s32 len);
			};
		}
	}
}

#endif