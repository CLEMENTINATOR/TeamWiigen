#include <libwiisys.h>

using namespace Libwiisys;

/**
 * \brief abstract destructor implemetation.
 */
Object::~Object()
{}

std::string Object::GetType()
{
	return "Libwiisys::Object";	
}
std::string Object::ToString()
{
	return GetType();
}	
	