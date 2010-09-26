#ifndef _NANDFILE_H_
#define _NANDFILE_H_

#include <string>

#include <ogcsys.h>

#include "File.h"
namespace Libwiisys {
	namespace IO {

		/**
		 * \class NandFile
		 * \see File
		 * \author Arasium, Teton, Fanta
		 * \version 1.0
		 * \brief This class handle ISFS-File use
		 */
		class NandFile : public File
		{
		public:
			virtual std::string GetType();
			/**
			 * @brief Create a NandFile
			 * @param fileName The file name of the file you want to create
			 * @return A reference on the new NandFile
			 * @see File& File::Create(const string &fileName)
			 */
			static NandFile& Create(const std::string &fileName);

			/**
			 * @brief Open the NandFile
			 * @param fileName the NandFile you want to open
			 * @param mode Could be ISFS_OPEN_WRITE etc
			 * @see FileMode
			 * @return A reference on the opened NandFile
			 * @see File& File::Open(const string &fileName, FileMode mode)
			 */
			static NandFile& Open(const std::string &fileName, u8 mode);

			/**
			 * \brief Delete a file
			 * \param fileName The fullpath of the file
			 * \see void File::Delete(const string &fileName)
			 */
			static void Delete(const std::string &fileName);

			/*!
			 * \brief Check if the file exists
			 * \param fileName The fullpath of the file
			 * \return true if the file exists, else false if it doesn't
			 * \see bool File::Exists(const string &fileName)
			 */
			static bool Exists(const std::string &fileName);

			/**
			 * @brief Write a buffer to the file
			 * @param b the buffer to write
			 * @see Buffer
			 */
			void Write(const Buffer& b);

			/**
			 * @brief Reads a file
			 * @param b The buffer where the read data will be stocked on
			 * @param len the length you want to read
			 * @return the number of read chars
			 */
			u32 Read(Buffer& b,u32 len, u32 offset = -1);

			void Seek(u32 offset);

			/**
			 * @brief Close the NandFile
			 */
			void Close();

			/**
			 * @brief Destructor
			 */
			virtual ~NandFile();
		private:
			s32 _fd;
			Buffer _rest;

			/**
			 * @brief Private constructor
			 * @param fd the file descriptor
			 * @param fileName the file name
			 * @return An instance of NandFile
			 */
			NandFile(s32 fd, const std::string &fileName);

		};
	}
}

#endif
