#ifndef _FATFILE_H_
#define _FATFILE_H_

#include <string>
#include <stdio.h>

#include <ogcsys.h>

#include "File.h"
#include "Device.h"

namespace Libwiisys {
	namespace IO {
		/**
		 * \class FatFile
		 * \see File
		 * \author Arasium, Teton, Fanta
		 * \version 1.0
		 * \brief Handle fat file (none-isfs) use
		 */
		class FatFile : public File
		{
		public:

			/**
			 * @brief Create a FatFile
			 * @param fileName The file name of the file you want to create
			 * @return A reference on the new FatFile
			 * @see File& File::Create(const string &fileName)
			 */
			static FatFile& Create(const std::string &fileName);

			/**
			 * @brief Open the FatFile
			 * @param fileName the FatFile you want to open
			 * @param mode Could be rw,r,w etc
			 * @return A reference on the opened FatFile
			 * @see File& File::Open(const string &fileName, FileMode mode)
			 */
			static FatFile& Open(const std::string &fileName, const std::string &mode);

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
			u32 Read(Buffer& b,u32 len);

			/**
			 * @brief Close the FatFile
			 */
			void Close();

			/**
			 * @brief Destructor
			 */
			virtual ~FatFile();
		private:
			FILE *_fd;

			/**
			 * @brief Private constructor
			 * @param fd the file descriptor
			 * @param fileName the file name
			 * @return An instance of FatFile
			 */
			FatFile(FILE *fd, const std::string &fileName);
		};
	}}
#endif
