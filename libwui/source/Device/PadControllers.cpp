#include <libwui/Device/PadControllers.hpp>
#include <Libwui/Resources/ImageResourceManager.hpp>
#include <Libwiisys/Exceptions/SystemException.h>

using namespace Libwui::Device;
using namespace Libwui::Resources;
using namespace Libwiisys::Exceptions;

PadController::PadController() : enabled(false), padImage("")
{}

PadController* PadController::Currents()
{
  static PadController *userInput = new PadController[4];
  return userInput;
}

void PadController::LoadCursorImages(int channel, const std::string& im, int offsetLeft, int offsetTop)
{
  if(channel < 0 || channel > 3)
    throw SystemException("Invalid wiimote index.", channel);

  Currents()[channel].padImage = im;
  Currents()[channel].offsetLeft = offsetLeft;
  Currents()[channel].offsetTop = offsetTop;
  Currents()[channel].enabled = (ImageResourceManager::Get(im) != NULL);
}

int PadController::NumberOfDefinedCursors()
{
  int lastCursor = 0;
  while(lastCursor < 4)
  {
    if(!Currents()[lastCursor].enabled)
      return lastCursor;

    lastCursor++;
  }

  return lastCursor;
}
