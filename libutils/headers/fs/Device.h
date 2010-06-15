#ifndef _DEVICE_H_
#define _DEVICE_H_

#include <string>
#include <vector>

#include "../Object.h"
#include <fat.h>

#define WII_ROOT_DIRECTORY "wii"
/**
*\struct fatDevice
*\brief Reprensents a fatDevice
*/
typedef struct {
	/** Device mount point */
	const std::string mount;
	/** Device name */
	const std::string name;

	/** Device interface */
	const DISC_INTERFACE *interface;

	/** To know how many item still use the device */
	u32 deviceHandles;
  
  /** To know if the interface has already been started */
  bool started;

} fatDevice;

/**
*\class Device
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

#endif
