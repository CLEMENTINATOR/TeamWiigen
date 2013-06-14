#ifndef _FATDIRECTORY_H_
#define _FATDIRECTORY_H_

#include "../Object.h"
#include <string>
#include <vector>
namespace Libwiisys
{
  namespace IO
  {
    /**
     * \class FatDirectory
     * \see Directory
     * \author Arasium, Teton, Fanta
     * \version 1.0
     * \brief Handle fat directory (none-isfs) use
     */
    class FatDirectory : public Object
    {
      public:
        virtual std::string GetType();
        
        static void Rename(const std::string &oldname, const std::string &newname);
        /**
         *\brief Create the given directory
         *\param name The absolute path of the directory
         *\see void Directory::Create(const string &name)
         */
        static void Create(const std::string &name);

        /**
         * \brief Delete the given directory
         *  \param name The absolute path of the directory
         *  \see void Directory::Delete(const string &name)
         */
        static void Delete(const std::string &name);

        /**
         * \brief Check if the directory exists
         *  \param name The absolute path of the directory
         * \return true if directory exists, else false
         * \see void Directory::Exists(const string &name)
         */
        static bool Exists(const std::string &name);

        /*!
         * \brief Get all the files of the directory
         * \param path The full path of the directory
         * \return An array of string containing the name of the files in the directory
         * \see vector<string> Directory::GetFiles(const string &name)
         */
        static std::vector<std::string> GetFiles(const std::string & path);

        /*!
         * \brief Get all the sub-directories of the directory
         * \param path The full path of the directory
         * \return An array(vector) of string containing the name of the sub-directories in the directory
         * \see vector<string> Directory::GetDirectories(const string & path)
         */
        static std::vector<std::string> GetDirectories(const std::string & path);
    };
  }
}
#endif
