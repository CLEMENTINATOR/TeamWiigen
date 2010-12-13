#include <Libwiisys/IO/File.h>
#include <Libwiisys/Exceptions/Exception.h>
#include <Libwui/Audio/MP3SongPlayer.h>
#include <ogc/machine/processor.h>
#include <limits.h>
#include <asndlib.h>

using namespace std;
using namespace Libwiisys;
using namespace Libwiisys::IO;
using namespace Libwiisys::Exceptions;
using namespace Libwui::Audio;

typedef union {
	struct {
		u16 hi;
		u16 lo;
	} aword;
	u32 adword;
} dword;

static void DTCallback(s32 param)
{
	MP3SongPlayer::Current()->DataTransferCallback();
}

MP3SongPlayer*& MP3SongPlayer::Current()
{
	static MP3SongPlayer* _current(NULL);
	return _current;
}

MP3SongPlayer::MP3SongPlayer(const std::string& file)
  : _data(File::ReadToEnd(file)),
		_nbLus(0),
		_outputIndex(0),
		_playing(false),
		_needToStop(true),
		_hasSample(false)
{
	MP3SongPlayer::Current() = this;
}


MP3SongPlayer::MP3SongPlayer(Libwiisys::Buffer& buffer)
  : _data(buffer),
		_nbLus(0),
		_outputIndex(0),
		_playing(false),
		_needToStop(true),
		_hasSample(false)
{
	MP3SongPlayer::Current() = this;
}

void MP3SongPlayer::Play()
{
	_needToStop = false;
	
	memset(_outputBuffers[0],0,ADMA_BUFFERSIZE);
	memset(_outputBuffers[1],0,ADMA_BUFFERSIZE);
	
	LWP_InitQueue(&_queue);
		
	mad_stream_init(&Stream);
	mad_frame_init(&Frame);
	mad_synth_init(&Synth);
	
	if(LWP_CreateThread(&_thread, ISongPlayer::Play, this, _stack, MP3_PLAYER_STACKSIZE, 80)<0)
		throw Exception("Cannot start the player thread.");
}

void MP3SongPlayer::Stop()
{
  Pause();
	_nbLus = 0;
}

void MP3SongPlayer::Pause()
{
  if(!_needToStop)
  {
    _needToStop = true;
    LWP_JoinThread(_thread,NULL);
  }
}

void MP3SongPlayer::Resume()
{
	_needToStop = false;
	if(LWP_CreateThread(&_thread, ISongPlayer::Play, this, _stack, MP3_PLAYER_STACKSIZE, 80)<0)
		throw Exception("Cannot start the player thread.");
}

void MP3SongPlayer::AsyncPlayer()
{
	bool lastFrame = false;
	mad_timer_t Timer;
	
	mad_timer_reset(&Timer);
	
	while(!lastFrame && !_needToStop)
	{
		try
		{
			if(!FeedData(lastFrame))
				continue;
		}
		catch(...)
		{
			break;
		}
		
		mad_timer_add(&Timer,Frame.header.duration);
		mad_synth_frame(&Synth,&Frame);

		Resample();
	}
	
	mad_synth_finish(&Synth);
	mad_frame_finish(&Frame);
	mad_stream_finish(&Stream);
	
	while(_playing)
		LWP_ThreadSleep(_queue);
	
	SND_StopVoice(0);
	
	LWP_CloseQueue(_queue);
}

bool MP3SongPlayer::FeedData(bool& lastFrame)
{
	u8 *GuardPtr = NULL;
	lastFrame = false;
	
	if(Stream.buffer == NULL || Stream.error == MAD_ERROR_BUFLEN) 
	{
		s32 toRead = DATABUFFER_SIZE;
		s32 rest = 0;

		//if there is a rest from the previous physical frame
		//keep it and read less data from the input stream
		if(Stream.next_frame!=NULL) 
		{
			rest = Stream.bufend - Stream.next_frame;
			memmove(_currentFrame.Content(), Stream.next_frame, rest);
			_currentFrame.Truncate(rest);
			toRead -= rest;
		}

		//get the new data
		if(_nbLus >= _data.Length())
		{
			u32 gpointerOffset = _currentFrame.Length();
			Buffer fill((u8)0, MAD_BUFFER_GUARD);
			_currentFrame.Append(fill);
			GuardPtr = (u8*)_currentFrame.Content() + gpointerOffset;
			toRead = MAD_BUFFER_GUARD;
			lastFrame = true;
		}
		else
		{
			u32 realRead = toRead;
			if(_nbLus + toRead > _data.Length())
				realRead = _data.Length() - _nbLus;
			_currentFrame.Append((u8*)_data.Content() + _nbLus, realRead);
			_nbLus += realRead;
		}

		mad_stream_buffer(&Stream, (const u8*)_currentFrame.Content(),_currentFrame.Length());
	}

	//decode the data and manage possible errors
	if(mad_frame_decode(&Frame,&Stream)) 
	{
		if(MAD_RECOVERABLE(Stream.error)) 
		{
			if(Stream.error != MAD_ERROR_LOSTSYNC || Stream.this_frame != GuardPtr) 
				return false;
		} 
		else if(Stream.error != MAD_ERROR_BUFLEN) 
			throw Exception("Error reading mp3 stream.");
	}
	
	return true;
}

void MP3SongPlayer::Resample()
{
	u16 val16;
	u32 val32;
	dword pos;
	s32 incr;

	pos.adword = 0;
	incr = (u32)(((f32)Frame.header.samplerate / 48000.0F) * 65536.0F);
	while(pos.aword.hi < Synth.pcm.length) 
	{
		val16 = _eqs[0].Do(FixedToShort(Synth.pcm.samples[0][pos.aword.hi]));
		val32 = (val16<<16);

		//if stereo
		if(MAD_NCHANNELS(&Frame.header) == 2) 
			val16 = _eqs[1].Do(FixedToShort(Synth.pcm.samples[1][pos.aword.hi]));
		val32 |= val16;
		
		if(_outputRing.Put(&val32, sizeof(u32), _queue))
		{
			memset(CurrentBuffer(), 0, ADMA_BUFFERSIZE);
			_hasSample = 0;
			SND_SetVoice(0, VOICE_STEREO_16BIT, 48000, 0, CurrentBuffer(), ADMA_BUFFERSIZE, _volume, _volume, DTCallback);
			_outputIndex ^= 1;
		}
		
		pos.adword += incr;
	}
}

s16 MP3SongPlayer::FixedToShort(mad_fixed_t fixed)
{
	/* Clipping */
	if(fixed >= MAD_F_ONE)
		return(SHRT_MAX);
	if(fixed <= -MAD_F_ONE)
		return(-SHRT_MAX);

	fixed= fixed >> (MAD_F_FRACBITS-15);
	return((s16)fixed);
}

void MP3SongPlayer::DataTransferCallback()
{
	if(_needToStop) 
	{
		_playing = (_outputRing.Get(CurrentBuffer(), ADMA_BUFFERSIZE, _queue)>0);
		return;
	}
	if(_hasSample)
	{
		if(SND_AddVoice(0,CurrentBuffer(),ADMA_BUFFERSIZE)==SND_OK) 
		{
			_hasSample = false;
			_outputIndex ^= 1;
		}
	}
	if(!(SND_TestPointer(0,CurrentBuffer()) && SND_StatusVoice(0)!=SND_UNUSED)) 
	{
		if(!_hasSample) 
		{
			_playing = (_outputRing.Get(CurrentBuffer(), ADMA_BUFFERSIZE, _queue)>0);
			_hasSample = true;
		}
	}
}

u8* MP3SongPlayer::CurrentBuffer()
{
	return _outputBuffers[_outputIndex];
}
