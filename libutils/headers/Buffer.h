#ifndef _BUFFER_H_
#define _BUFFER_H_

#include <gctypes.h>
#include "../Object.h"

namespace Libwiisys {

/*! \class Buffer
 * \brief This class can store data and will automatically manage pointers in order to avoid memory leaks
 * \author Arasium, Teton, Fanta
 * \version 1.0
 */

class Buffer : public Object
{
private:
	u64 _length;
	void* _innerBuffer;
	u64 _checksum;

public:
	Buffer(const void* content = NULL, const u64 length = 0);
	Buffer(const u8 value, const u64 length);
	Buffer(const Buffer& b);
	Buffer& operator=(const Buffer& b);
	bool operator==(const Buffer &buf);
	~Buffer();

	void Append(const void* content, const u64 length);
	void Append(const Buffer& b);

	void Clear();
	void* Content() const;
	u64 Length() const;

	void Truncate(const u64 position);
	bool ValidateSHA1(const Buffer& sha);
	u64 Checksum();
	u64 Find(const Buffer&b);
};

}

#endif
