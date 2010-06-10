/*
 * NetworkUtility.cpp
 *
 *  Created on: 10 juin 2010
 *      Author: Clement
 */

#include <com/NetworkUtility.h>
#include <exception/Exception.h>
#include <network.h>
static char hostip[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
using namespace std;


NetworkUtility::NetworkUtility() {

}

NetworkUtility::~NetworkUtility() {

}
NetworkUtility &NetworkUtility::Current()
{
	static NetworkUtility n;
	return n;


}
/*!
* \brief Gets the wii IP
* \return the ip on a string array
*
*/
string NetworkUtility::GetIp(void)
{
	static bool initialized = false;

	if(!initialized)
	{
		s32 ret  = if_config(hostip, NULL, NULL, true);
		if (ret < 0)
			throw Exception("Error initialising network !",ret);

		initialized = true;
	}
	return string(hostip);
}
