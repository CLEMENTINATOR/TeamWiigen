#include <malloc.h>
#include <cstring>
#include <libwiisys.h>

using namespace Libwiisys;
using namespace Libwiisys::Exceptions;

/**
 * \brief  Overloaded Constructor
 * \param content Pointer to the data
 * \param length The data length
 *
 * It will initialize the buffer with the data provided.
 **/
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

/**
 * \brief  Overloaded Constructor, fill the buffer with value
 * \param value A simple value
 * \param length The data length
 *
 * The buffer will be filled with value. The total size of the buffer is length.
 * This is like memset.
 **/
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

/**
 * \brief  Copy Constructor
 * \param b The buffer
 **/
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

/**
 * \brief  Overloaded = operator
 * \param b A buffer
 * \return A totally new buffer.
 *
 * Be carrefull, the datas in the buffer will be duplicated.
 * Ie, a modification of b won't affect the second buffer.
 **/
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

/**
 * \brief Destructor
 *
 * This will also free the inner datas
 */
Buffer::~Buffer()
{
	if (_innerBuffer)
		free(_innerBuffer);

	_innerBuffer = NULL;
}

/**
 * \brief  Append data to the buffer (the data is copied)
 * \param content Content to add to the buffer
 * \param length The content length
 **/
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

/**
 * \brief  Append the buffer to the current buffer( the buffer content is copied)
 * \param b The buffer to add
 **/
void Buffer::Append(const Buffer& b)
{
	Append(b.Content(), b.Length());

}

/**
 *\brief  Clear the buffer
 **/
void Buffer::Clear()
{
	if (_innerBuffer)
		free(_innerBuffer);

	_innerBuffer = NULL;
	_length = 0;
	_checksum = 0;
}

/**
 *\brief  Returns the buffer data
 *\return The innerbuffer of the Buffer
 **/
void* Buffer::Content() const
{
	return _innerBuffer;
}

/**
 *\brief  Returns the buffer length
 *\return The length of the Buffer data
 **/
u64 Buffer::Length() const
{
	return _length;
}

/**
 *\brief Truncate the buffer to the position
 *\param position The position to truncate the buffer
 **/
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

/**
 *\brief  Returns the buffer checkSum
 *\return The checkSum of the Buffer
 **/
u64 Buffer::Checksum()
{
	return _checksum;
}

/**
 *\brief Check the sha of the buffer
 *\param sha The buffer containing sha hash
 *\return true if hash matches with sha hash
 */
bool Buffer::ValidateSHA1(const Buffer& sha)
{
	u8 hash[20];
	SHA1((u8*)_innerBuffer, _length, hash);
	return memcmp((u8*)hash, (u8*)sha._innerBuffer, 20) == 0;
}

/**
 *\brief Overloaded == operator
 *\param b The buffer you need to compare with this
 */
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

/**
 *\brief Find the buffer in the other buffer
 *\param b The buffer you need to find in this
 *\return The index of the founded buffer, or the length of the buffer
 */
u64 Buffer::Find(const Buffer&b)
{
	u64 index=0;

	for(index=0;index<_length-b.Length();index++)
	{
		if(memcmp((u8*)(_innerBuffer)+index,(u8*)b.Content(),b.Length())==0)
			return index;
	}
	return _length;
}
