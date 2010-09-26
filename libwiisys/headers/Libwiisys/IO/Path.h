#ifndef _PATH_H_
#define _PATH_H_

#include "../Object.h"
#include <string>
namespace Libwiisys {
	namespace IO {

		/**
		 *\class Path
		 *\brief A tool Class who allow to play with paths
		 *\author Arasium, Teton, Fanta
		 *\version 1.0
		 *
		 */

		class Path : public Object
		{
		public:
			virtual std::string GetType();
			/*!
			 * \brief Get the root of the path
			 * \param path A file/directory path
			 * \return the root, as "wii:/" or "sd:/"
			 */
			static std::string GetRoot(const std::string &path);

			/*!
			 * \brief Get the root name of the path
			 * \param path A file/directory path
			 * \return the root name, as "wii" or "sd"
			 */
			static std::string GetRootName(const std::string &path);

			/*!
			 * \brief Get the parent directory of the file/directory path
			 * \param path A file/directory path
			 * \return the access path of the parent directory
			 */
			static std::string GetParentDirectory(const std::string &path);

			/*!
			 * \brief Get the file name of the given path
			 * \param path A file path
			 * \return the file name
			 */
			static std::string GetFileName(const std::string &path);

			/*!
			 * \brief Get the directory name of the given path
			 * \param path A file path
			 * \return the directory name
			 */
			static std::string GetDirectoryName(const std::string &path);

			/*!
			 * \brief Get the file name without extension of the given path
			 * \param path A file path
			 * \return the file name without this extension
			 * \see string Path::GetFileName(const string &path)
			 */
			static std::string GetFileNameWithoutExtension(const std::string &path);

			/*!
			 * \brief Get the file extension
			 * \param path A file path
			 * \return the extension type (as dol/elf ect)
			 */
			static std::string GetFileExtension(const std::string &path);

			/*!
			 * \brief Cleans the given path
			 * \param path A file path
			 * \return the new cleaned path
			 */
			static std::string CleanPath(const std::string &path);
		};
	}
}
#endif
