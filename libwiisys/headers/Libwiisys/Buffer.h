#ifndef _BUFFER_H_
#define _BUFFER_H_

#include <gctypes.h>
#include "Object.h"

namespace Libwiisys {

	/*! \class Buffer
	 * \brief Use this to avoid memory leaks
	 * \author Arasium, Teton, Fanta
	 * \version 1.0
	 *
	 * This class can store data and will automatically manage pointers.
	 */

	class Buffer : public Object
	{
	private:
		u64 _length;
		void* _innerBuffer;
		u64 _checksum;

	public:
		virtual std::string GetType();
		/**
		 * \brief  Overloaded Constructor
		 * \param content Pointer to the data
		 * \param length The data length
		 *
		 * It will initialize the buffer with the data provided.
		 **/
		Buffer(const void* content = NULL, const u64 length = 0);

		/**
		 * \brief  Overloaded Constructor, fill the buffer with value
		 * \param value A simple value
		 * \param length The data length
		 *
		 * The buffer will be filled with value. The total size of the buffer is length.
		 * This is like memset.
		 **/
		Buffer(const u8 value, const u64 length);

		/**
		 * \brief  Copy Constructor
		 * \param b The buffer
		 **/
		Buffer(const Buffer& b);

		/**
		 * \brief  Overloaded = operator
		 * \param b A buffer
		 * \return A totally new buffer.
		 *
		 * Be carrefull, the datas in the buffer will be duplicated.
		 * Ie, a modification of b won't affect the second buffer.
		 **/
		Buffer& operator=(const Buffer& b);

		/**
		 *\brief Overloaded == operator
		 *\param buf The buffer you need to compare with this
		 */
		bool operator==(const Buffer &buf);

		/**
		 * \brief Destructor
		 *
		 * This will also free the inner datas
		 */
		~Buffer();

		/**
		 * \brief  Append data to the buffer (the data is copied)
		 * \param content Content to add to the buffer
		 * \param length The content length
		 **/
		void Append(const void* content, const u64 length);

		/**
		 * \brief  Append the buffer to the current buffer( the buffer content is copied)
		 * \param b The buffer to add
		 **/
		void Append(const Buffer& b);

		/**
		 *\brief  Clear the buffer
		 **/
		void Clear();

		/**
		 *\brief  Returns the buffer data
		 *\return The innerbuffer of the Buffer
		 **/
		void* Content() const;

		/**
		 *\brief  Returns the buffer length
		 *\return The length of the Buffer data
		 **/
		u64 Length() const;

		/**
		 *\brief Truncate the buffer to the position
		 *\param position The position to truncate the buffer
		 **/
		void Truncate(const u64 position);

		/**
		 *\brief Check the sha of the buffer
		 *\param sha The buffer containing sha hash
		 *\return true if hash matches with sha hash
		 */
		bool ValidateSHA1(const Buffer& sha);

		/**
		 *\brief  Returns the buffer checkSum
		 *\return The checkSum of the Buffer
		 **/
		u64 Checksum();

		/**
		 *\brief Find the buffer in the other buffer
		 *\param b The buffer you need to find in this
		 *\return The index of the founded buffer, or the length of the buffer
		 */
		u64 Find(const Buffer&b);
	};

}

#endif
