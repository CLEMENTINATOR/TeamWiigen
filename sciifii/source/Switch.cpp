#include <Sciifii.h>

using namespace std;

Switch::Switch(string name, bool active, string value)
{
	Name = name;
	Value = value;
	Activated = active;
}