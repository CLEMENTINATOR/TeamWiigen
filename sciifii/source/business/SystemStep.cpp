#include <sstream>
#include <iostream>
#include <iomanip>
#include <Libwiisys/Exceptions/Exception.h>
#include <Libwiisys/logging/Log.h>
#include <sciifii/business/SystemStep.h>
#include <sciifii/Config.h>
#include <sciifii/Tools.h>
#include <gccore.h>


using namespace std;
using namespace Libwiisys::Logging;
using namespace Libwiisys::Exceptions;
using namespace Libwiisys;


SystemStep::SystemStep(string action, string message) :
    _action(action), _message(message)
{}

bool SystemStep::Prepare()
{
  return true;
}

void SystemStep::Install()
{
  cout << "Sciifii will now " << _action << endl;
  if (_message != "")
  {
     cout << "Reason : " << _message << endl;   
  }
  cout << "Press A to " << _action << endl;
  Pause();
  if (_action == "reboot")
  {
     SYS_ResetSystem(SYS_RESTART,0,0);
  }
  else
  {
    exit(0);
  }
}

void SystemStep::SendtoLog()
{
  stringstream str;
  str << "SystemStep(" << _action << "," << _message  <<  ")";
  Log::WriteLog(Log_Info, str.str());
}