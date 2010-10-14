#ifndef _UI_COMPONENT_IMAGE_H_
#define _UI_COMPONENT_IMAGE_H_

#include "../Control.hpp"
#include <string>

namespace Libwui
{
  namespace Component
  {
    typedef enum
    {
      ResizeMode_None,
      ResizeMode_Fill,
      ResizeMode_FitToFill,
    } ResizeMode;

    class Image : public Control
    {
      private:
        ResizeMode _mode;
        std::string _imagePath;

      public:
        Image();
        void ProcessMessage(Message& message);

        void FillMode(ResizeMode mode);
        ResizeMode FillMode() const;
        void ImageLocation(const std::string& location);
        std::string ImageLocation() const;
        void Draw();
    };
  }
}

#endif
