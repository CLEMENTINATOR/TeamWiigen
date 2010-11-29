#include <sciifii/business/StopSciifiiStep.h>
#include <sciifii/business/common/ExitSciifiiException.h>
#include <Libwiisys/logging/Log.h>

using namespace Libwiisys::Logging;

bool StopSciifiiStep::Prepare()
{
  return true;
}

void StopSciifiiStep::Install()
{
	ExitSciifiiException ex;
	throw ex;
}

void StopSciifiiStep::SendToLog()
{
  Log::WriteLog(Log_Info,"StopSciifiiStep");
}