#include <libwiisys.h>

using namespace std;
using namespace Libwiisys;

/**
 * \brief abstract destructor implemetation.
 */
Object::~Object()
{}

string Object::GetType()
{
	return "Libwiisys::Object";	
}
string Object::ToString()
{
	return GetType();
}	

namespace Libwiisys
{
ostream& operator<< ( ostream& theStream, Object& obj)
{
	theStream << obj.ToString();
	return theStream;
}
}