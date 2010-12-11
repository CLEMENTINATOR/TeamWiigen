#include <Libwiisys/IO/Path.h>
#include <Libwiisys/Exceptions/Exception.h>
#include <Libwui/Audio/PlayerFactory.h>
#include <Libwui/Audio/MP3SongPlayer.h>

using namespace std;
using namespace Libwiisys::IO;
using namespace Libwiisys::Exceptions;
using namespace Libwui::Audio;

ISongPlayer& PlayerFactory::GetPlayer(const string& fileName)
{
	string ext = Path::GetFileExtension(fileName);
	
	if(ext == "mp3" || ext == "MP3")
		return *(new MP3SongPlayer(fileName));
	
	throw Exception("Song type not recognized: " + fileName);
}
