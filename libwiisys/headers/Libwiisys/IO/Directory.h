#ifndef _DIRECTORY_H_
#define _DIRECTORY_H_

#include "../Object.h"
#include <string>
#include <vector>

namespace Libwiisys
{
  namespace IO
  {
    /**
     *\class Directory
     *\brief Represents a directory
     * \author Arasium, Teton, Fanta
     * \version 1.0
     **/
    class Directory : public Object
    {
      public:
        virtual std::string GetType();
        /*!
         * \brief Create a new directory
         * \param name The fullpath of the file
         */
        static void Create(const std::string &name);
        
        static void Rename(const std::string &oldname, const std::string &newname);

        /*!
         * \brief Delete a directory
         * \param name The full path of the directory
         * \param recursive If true, it'll delete all the sub-directories/files of the directory
         */
        static void Delete(const std::string &name, bool recursive = false);

        /*!
         * \brief Copy the directory a an other enplacement(same as ctrl-c / ctrl-v)
         * \param name The name of the directory
         * \param dest the copy destination
         * \param recursive If true , it'll copy all the subdirectories in dest too
         */
        static void Copy(const std::string &name, const std::string &dest, bool recursive = false);

        /*!
         * \brief Cut a directory and paste it in destination (ctrl-x / ctrl-v)
         * \param name The name of the directory
         * \param dest The name of the destination directory
         */
        static void Move(const std::string &name, const std::string &dest);

        /*!
         * \brief Check if the directory exists
         * \param name The fullpath of the directory
         * \return true if the directory exists, else false if it doesn't
         */
        static bool Exists(const std::string &name);

        /*!
         * \brief Get all the files of the directory
         * \param name The full path of the directory
         * \return An array of string containing the name of the files in the directory
         */
        static std::vector<std::string> GetFiles(const std::string &name);

        /*!
         * \brief Get all the sub-directories of the directory
         * \param name The full path of the directory
         * \return An array(vector) of string containing the name of the sub-directories in the directory
         */
        static std::vector<std::string> GetDirectories(const std::string &name);

        /*!
         * \brief Check if the directory is empty
         * \param name The name of the directory
         * \return true if the directory is empty, false if it isn't
         */
        static bool IsEmpty(const std::string &name);
        /*!
         * \brief "Cleans" the path( Change all the // into /)
         * \param name The filePath who needs to be cleaned
         * \return The new cleaned file path
         */
        static std::string CleanPath(const std::string &path);
    };
  }
}
#endif
