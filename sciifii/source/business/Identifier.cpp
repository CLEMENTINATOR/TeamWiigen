#include <sstream>

#include <Sciifii.h>

using namespace std;
using namespace Libwiisys::System::Security;
using namespace Libwiisys::Logging;

Identifier::Identifier(UserType type)
: Installer(),
	_type(type)
{}

bool Identifier::Prepare()
{
  return true;
}

void Identifier::Install()
{
	stringstream txt;
	txt << "Identify as " << _type;
	OnProgress(txt.str(), 1);
	Identification::IdentifyAs(_type);
}
void Identifier::SendToLog()
{
	stringstream txt;
	txt << "Identifier("<< _type <<" )";
	Log::WriteLog(Log_Info,txt.str());
}
