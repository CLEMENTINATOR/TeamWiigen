#ifndef _FILE_H_
#define _FILE_H_

#include <string>
#include <ogcsys.h>
#include "../Object.h"
#include "../Buffer.h"
#include "FileMode.h"

namespace Libwiisys
{
  namespace IO
  {

    /**
     *\class File
     *\brief Represents a file
     * \author Arasium, Teton, Fanta
     * \version 1.0
     **/
    class File : public Object
    {
      protected:
        /** the file name */
        std::string _fileName;
        /** the file length */
        u32 _fileLength;

      public:
        virtual std::string GetType();
        /*!
         * \brief Create a new file
         * \param fileName The fullpath of the file
         * \return The new file (opened)
         */
        static File& Create(const std::string &fileName);


        /*!
         * \brief Open a file
         * \param fileName The fullpath of the file
         * \param mode Opening FileMode(R,W,RW)
         * \see FileMode
         * \return The opened file
         */
        static File& Open(const std::string &fileName, FileMode mode);

        
        static void Rename(const std::string &oldname, const std::string &newname);
        /*!
         * \brief Delete a file
         * \param fileName The fullpath of the file
         */
        static void Delete(const std::string &fileName);

        /*!
         * \brief Check if the file exists
         * \param fileName The fullpath of the file
         * \return true if the file exists, else false if it doesn't
         */
        static bool Exists(const std::string &fileName);

        /*!
         * \brief Read into a buffer
         * \param fileName The fullpath of the file
         * \return The contents of the files, on a Buffer Object
         */
        static Buffer ReadToEnd(const std::string &fileName);

        /**
         * @brief Write to the file( need to be reimplemented if you inherit this class)
         * @param b The buffer to write
         */
        virtual void Write(const Buffer& b) = 0;

				void Write(const std::string& text);
				void Write(const char* text);
				
        /**
         * @brief Read to the file( need to be reimplemented if you inherit this class)
         * @param b The buffer where readed data will e stored
         * @param len The len to read
         * @return The len read
         */
        virtual u32 Read(Buffer& b,u32 len, u32 offset = -1) = 0;

        virtual void Seek(u32 offset) = 0;

        /*!
         * \brief Close the opened file
         */
        virtual void Close() = 0;

        /*!
         * \brief Get file length
         * \return The file length
         */
        u32 Size() const;

        /*!
         * \brief Destructor
         */
        virtual ~File() = 0;

        /*!
         * \brief Copy a file
         * \param fileToCopy The fullpath of the file to copy
         * \param fileCopied The fullpath of the destination path
         */
        static void Copy(const std::string &fileToCopy,const std::string &fileCopied);

        /*!
         * \brief Cut a file
         * \param fileToCopy The fullpath of the file to copy
         * \param fileCopied The fullpath of the destination path
         */
        static void Move(const std::string &fileToCopy,const std::string &fileCopied);
    };
  }
}
#endif
