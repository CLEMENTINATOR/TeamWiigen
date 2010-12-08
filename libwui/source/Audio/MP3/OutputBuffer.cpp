#include <Libwui/Audio/MP3/OutputBuffer.h>
#include <ogc/machine/processor.h>

using namespace Libwui::Audio::MP3;

OutputBuffer::OutputBuffer()
{
	buf_filled = false;
	put = get = (u32*)buffer;
}

s32 OutputBuffer::Used()
{
	return ((DATABUFFER_SIZE + ((u32)put - (u32)get)) % DATABUFFER_SIZE);
}

s32 OutputBuffer::Space()
{
	return ((DATABUFFER_SIZE - ((u32)put - (u32)get) - 1) % DATABUFFER_SIZE);
}

s32 OutputBuffer::Get(void *data, s32 len, lwpq_t queue)
{
	if(Used() < len)
		len = Used();

	if(len == 0)
	{
		LWP_ThreadSignal(queue);
		return 0;
	}
	
	u32* p = (u32*)data;
	s32 cnt = ((u32)buffer + DATABUFFER_SIZE - (u32)get);
	if(len > cnt)
	{
		for(s32 i = 0; i < (cnt >> 2); i++)
			*p++ = *get++;
		get = (u32*)buffer;
		for(s32 i = 0; i < ((len - cnt) >> 2); i++)
			*p++ = *get++;
	} 
	else 
	{
		for(s32 i = 0; i < (len >> 2); i++)
			*p++ = *get++;
	}

	DCFlushRangeNoSync(data,len);
	LWP_ThreadSignal(queue);
	_sync();
	
	return len;
}

bool OutputBuffer::Put(void *data, s32 len, lwpq_t queue)
{
	while(len > Space())
		LWP_ThreadSleep(queue);

	u32* p = (u32*)data;
	s32 cnt = ((u32)buffer + DATABUFFER_SIZE - (u32)put);
	if(len > cnt) 
	{
		for(s32 i = 0; i < (cnt >> 2); i++)
			*put++ = *p++;
		put = (u32*)buffer;
		for(s32 i = 0; i < ((len - cnt) >> 2); i++)
			*put++ = *p++;
	} 
	else 
	{
		for(s32 i = 0; i < (len >> 2); i++)
			*put++ = *p++;
	}

	if(!buf_filled && Used() >= (DATABUFFER_SIZE>>1)) 
	{
		buf_filled = true;
		return true;
	}

	return false;
}