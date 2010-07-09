#ifndef _DEVICE_H_
#define _DEVICE_H_

#include <string>
#include <vector>

#include "../Object.h"
#include "fatDevice.h"

#define WII_ROOT_DIRECTORY "wii"

/*! \namespace Libwiisys::IO
 * \brief File System elements
 *
 * Actually, this only contains fs items.
 */

namespace Libwiisys {namespace IO {

		/**
		 * \class Device
		 * \brief This class manage automatically wii devices
		 * \author Arasium, Teton, Fanta
		 * \version 1.0
		 **/
		class Device : public Object
		{
		public:

			/**
			 *\brief Check if there is no files left open and then shutdown all devices
			 */
			static void EnsureShutdown();

			/*!
			 * \brief Get avilable roots on the wii
			 * \return a string array with the roots
			 */
			static std::vector<std::string> GetAvailableRoots();

			/*!
			 * \brief Mount the device where the file path is on
			 * \param path A file path
			 */
			static void Mount(const std::string &path);

			/*!
			 * \brief Unmount where the file path is on
			 * \param path A file path
			 */
			static void UnMount(const std::string &path);

			/*!
			 * \brief Return if the path is a fat path or nor
			 * \param path A file path
			 * \return true if the path isn't a nand path,else false
			 */
			static bool IsFatPath(const std::string &path);

			/*!
			 * \brief Return a path which is used by ISFS storage access fonctions
			 * \param path A file path
			 * \return path which can be used for ISFS
			 */
			static std::string GetWiiPath(const std::string &path);

		private:

			/**
			 *\brief Find the device associated to pathName
			 *\param pathName A path name
			 *\return The fatDevice associated with pathName, or NULL if unexistant
			 */
			static fatDevice& FindDevice(const std::string &pathName);

			/*!
			 * \brief Mount device
			 * \param device The device to mount
			 * \see fatDevice
			 */
			static void Mount(fatDevice &device);

			/*!
			 * \brief Mount ISFS storage (Nand)
			 */
			static void Mount();

			/*!
			 * \brief UnMount device
			 * \param device The device to unmount
			 * \see fatDevice
			 */
			static void UnMount(fatDevice &device);

			/*!
			 * \brief UnMount ISFS storage (Nand)
			 */
			static void UnMount();
		};

	}}

#endif
