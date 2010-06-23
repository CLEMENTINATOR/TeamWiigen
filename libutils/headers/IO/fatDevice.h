#ifndef FATDEVICE_H_
#define FATDEVICE_H_
namespace Libwiisys {
	namespace IO{
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
}
}
#endif /* FATDEVICE_H_ */
