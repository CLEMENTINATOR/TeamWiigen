#include <libwui/Resources/Colors.h>

using namespace Libwui::Resources;

GXColor Colors::Black()
{
  return (GXColor){0,0,0,255};
}

GXColor Colors::Red()
{
  return (GXColor){255,0,0,255};
}

GXColor Colors::Green()
{
  return (GXColor){0,255,0,255};
}

GXColor Colors::Blue()
{
  return (GXColor){0,0,255,255};
}

GXColor Colors::White()
{
  return (GXColor){255,255,255,255};
}

GXColor Colors::Yellow()
{
  return (GXColor){255,255,0,255};
}

GXColor Colors::Magenta()
{
  return (GXColor){255,0,255,255};
}

GXColor Colors::Cyan()
{
  return (GXColor){0,255,255,255};
}

GXColor Colors::Transparent()
{
  return (GXColor){0,0,0,0};
}

GXColor Colors::FromRGBA(int r, int g, int b, int a)
{
  return (GXColor){r,g,b,a};
}

