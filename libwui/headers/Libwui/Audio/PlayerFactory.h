#ifndef _PLAYER_FACTORY_H_
#define _PLAYER_FACTORY_H_

#include <string>
#include <Libwiisys/Object.h>
#include "ISongPlayer.h"

namespace Libwui
{
	namespace Audio
	{
		class PlayerFactory : Libwiisys::Object
		{
		public:
			static ISongPlayer& GetPlayer(const std::string& fileName);
		};
	}
}
#endif