#include <malloc.h>
#include <cstring>
#include <com/buffer.h>
#include <exception/Exception.h>
#include <sha1.h>

Buffer::Buffer(const void* content, const u64 length)
        :  _length(length),
        _innerBuffer(NULL),
		_checksum(0)
{
    if (_length == 0)
        return;

    _innerBuffer = memalign(32, _length);
    if (!_innerBuffer)
        throw Exception("Not enough memory.", -1);

    memcpy(_innerBuffer, content, _length);
	
	for(u64 cindex = 0; cindex < _length; cindex++)
		_checksum += ((u8*)_innerBuffer)[cindex];
}

Buffer::Buffer(const u8 value, const u64 length)
        :  _length(length),
        _innerBuffer(NULL),
		_checksum(0)
{
    if (_length == 0)
        return;

    _innerBuffer = memalign(32, _length);

    if (!_innerBuffer)
        throw Exception("Not enough memory.", -1);

    memset(_innerBuffer, value, _length);

	for(u64 cindex = 0; cindex < _length; cindex++)
		_checksum += value;
}

Buffer::Buffer(const Buffer& b)
        :  _length(b._length),
        _innerBuffer(NULL),
		_checksum(b._checksum)
{
    if (_length == 0)
        return;

    _innerBuffer = memalign(32, _length);
	
    if (!_innerBuffer)
        throw Exception("Not enough memory.", -1);
		
    memcpy(_innerBuffer, b._innerBuffer, _length);
}

Buffer& Buffer::operator=(const Buffer& b)
{
    if (_innerBuffer)
        free(_innerBuffer);

    _innerBuffer = NULL;
    _length = b._length;

    if (_length == 0)
        return *this;

    _innerBuffer = memalign(32, _length);
    if (!_innerBuffer)
        throw Exception("Not enough memory.", -1);
    memcpy(_innerBuffer, b._innerBuffer, _length);

	_checksum = b._checksum;

    return *this;
}

Buffer::~Buffer()
{
    if (_innerBuffer)
        free(_innerBuffer);

    _innerBuffer = NULL;
}

void Buffer::Append(const void* content, const u64 length)
{
    if (length == 0)
        return;

    u8* tempBuffer = NULL;
    tempBuffer = (u8*)memalign(32, _length + length);
    if (!tempBuffer)
        throw Exception("Not enough memory.", -1);

    if (_length != 0)
        memcpy(tempBuffer, _innerBuffer, _length);

    memcpy(tempBuffer + _length, content, length);

    _length += length;
    if (_innerBuffer)
        free(_innerBuffer);

    _innerBuffer = tempBuffer;
	
	for(u64 cindex = 0; cindex < length; cindex++)
		_checksum += ((u8*)content)[cindex];
}

void Buffer::Append(const Buffer& b)
{
    Append(b.Content(), b.Length());

}

void Buffer::Clear()
{
    if (_innerBuffer)
        free(_innerBuffer);

    _innerBuffer = NULL;
    _length = 0;
	_checksum = 0;
}

void* Buffer::Content() const
{
    return _innerBuffer;
}

u64 Buffer::Length() const
{
    return _length;
}

void Buffer::Truncate(const u64 position)
{
    if (position >= _length)
        return;

    if (position == 0)
    {
        Clear();
        return;
    }

    u8* tempBuffer = NULL;
    tempBuffer = (u8*)memalign(32, position);
    if (!tempBuffer)
        throw Exception("Not enough memory.", -1);

    memcpy(tempBuffer, _innerBuffer, position);

    _length = position;
    free(_innerBuffer);

    _innerBuffer = tempBuffer;

	_checksum = 0;
	for(u64 cindex = 0; cindex < _length; cindex++)
		_checksum += ((u8*)_innerBuffer)[cindex];
}

u64 Buffer::Checksum()
{
    return _checksum;
}

bool Buffer::ValidateSHA1(const Buffer& sha)
{
	u8 hash[20];
	SHA1((u8*)_innerBuffer, _length, hash);
	return memcmp((u8*)hash, (u8*)sha._innerBuffer, 20) == 0;
}

bool Buffer::operator==(const Buffer &b)
{
   if(_checksum != b._checksum)
	 return false;
   else if(b._length != _length)
	 return false;
   else
	   for(u64 i = 0; i < _length; i++)
		   if(((u8*)_innerBuffer)[i] != ((u8*)b._innerBuffer)[i])
			 return false;
   
   return true;
}
