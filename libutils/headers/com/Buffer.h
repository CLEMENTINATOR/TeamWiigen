#ifndef _BUFFER_H_
#define _BUFFER_H_

#include <gctypes.h>
#include "../Object.h"

class Buffer : public Object
{
private:
	u64 _length;
	void* _innerBuffer;

public:
	Buffer(const void* content = NULL, const u64 length = 0);
	Buffer(const u8 value, const u64 length);
	Buffer(const Buffer& b);
	Buffer& operator=(const Buffer& b);
	~Buffer();

	void Append(const void* content, const u64 length);
	void Append(const Buffer& b);

	void Clear();
	void* Content() const;
	u64 Length() const;

	void Truncate(const u64 position);

	u64 Checksum();
};

#endif
