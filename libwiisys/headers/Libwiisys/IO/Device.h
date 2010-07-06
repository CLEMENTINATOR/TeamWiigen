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

namespace Libwiisys { namespace IO {

/**
 * \class Device
 * \brief This class manage automatically wii devices
 * \author Arasium, Teton, Fanta
 * \version 1.0
 **/
class Device : public Object
{
public:
	static void EnsureShutdown();
	static std::vector<std::string> GetAvailableRoots();
	static void Mount(const std::string &path);
	static void UnMount(const std::string &path);
	static bool IsFatPath(const std::string &path);
	static std::string GetWiiPath(const std::string &path);

private:
	static fatDevice& FindDevice(const std::string &pathName);
	static void Mount(fatDevice &device);
	static void Mount();
	static void UnMount(fatDevice &device);
	static void UnMount();
};

}}

#endif
