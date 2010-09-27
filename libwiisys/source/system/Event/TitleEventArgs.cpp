#include <libwiisys.h>

using namespace Libwiisys::System::Event;
using namespace std;

string TitleEventArgs::GetType()
{
  return "Libwiisys::System::Event::TitleEventArgs," + EventArgs::GetType();
}