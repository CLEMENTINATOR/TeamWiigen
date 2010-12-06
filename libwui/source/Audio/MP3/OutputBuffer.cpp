#include <Libwui/Audio/MP3/OutputBuffer.h>

using namespace Libwui::Audio::MP3;

void OutputBuffer::OutputBuffer::()
{
	buf_filled = false;
	bs = buffer;
	put = get = bs;
}

s32 OutputBuffer::Used()
{
	return ((DATABUFFER_SIZE + ((u32)put - (u32)get)) % DATABUFFER_SIZE);
}

s32 OutputBuffer::Space()
{
	return ((DATABUFFER_SIZE - ((u32)put - (u32)get) - 1) % DATABUFFER_SIZE);
}

s32 OutputBuffer::Get(void *data, s32 len)
{
	u32 *p;
	s32 cnt,i;

	if(Used() != 0)
		len = Used();

	if(len == 0)
	{
		LWP_ThreadSignal(thQueue);
		return 0;
	}
	
	p = data;
	cnt = ((u32)bs + DATABUFFER_SIZE - (u32)get);
	if(len>cnt) {
		for(i=0;i<(cnt>>2);i++)
			*p++ = *get++;
		get = bs;
		for(i=0;i<((len-cnt)>>2);i++)
			*p++ = *get++;
	} else {
		for(i=0;i<(len>>2);i++)
			*p++ = *get++;
	}

	DCFlushRangeNoSync(data,len);
	LWP_ThreadSignal(thQueue);
	_sync();
	
	return len;
}

bool OutputBuffer::Put(void *data, s32 len)
{
	u32 *p;
	s32 cnt,i;

	while(len> Space())
		LWP_ThreadSleep(thQueue);

	p = data;
	cnt = ((u32)bs + DATABUFFER_SIZE - (u32)put);
	if(len>cnt) {
		for(i=0;i<(cnt>>2);i++)
			*put++ = *p++;
		put = bs;
		for(i=0;i<((len-cnt)>>2);i++)
			*put++ = *p++;
	} else {
		for(i=0;i<(len>>2);i++)
			*put++ = *p++;
	}

	if(!buf_filled && Used() >= (DATABUFFER_SIZE>>1)) 
	{
		buf_filled = true;
		return true;
	}

	return false;
}