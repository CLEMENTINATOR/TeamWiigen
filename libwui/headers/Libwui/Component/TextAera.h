#ifndef _TEXT_AERA_H_
#define _TEXT_AERA_H_

#include "../Control.hpp"
#include "Label.hpp"
#include "TrackBar.hpp"
#include <Libwui/Resources/FontResource.hpp>

namespace Libwui
{
  namespace Component
  {
    class TextAera : public Control
    {
      public:
        TextAera(const std::string& text, int s = 12, GXColor c = (GXColor){255, 255, 255, 255});
        virtual ~TextAera();

        void InitializeComponents();

        virtual void ProcessMessage(Message& message);

        virtual void SetSize(int w, int h);

        void Text(const std::string& text);
        void SetFont(const std::string& font);
        void FontSize(int size);
        void ForeColor(GXColor c);
		void UpDefaultImage(const std::string& imagePath);
		std::string UpDefaultImage() const;
		void UpOverImage(const std::string& imagePath);
		std::string UpOverImage() const;
		void UpClickedImage(const std::string& imagePath);
		std::string UpClickedImage() const;
		void DownDefaultImage(const std::string& imagePath);
        std::string DownDefaultImage() const;
        void DownOverImage(const std::string& imagePath);
        std::string DownOverImage() const;
        void DownClickedImage(const std::string& imagePath);
        std::string DownClickedImage() const;
        void ScrollBarImage(const std::string& imagePath);
		std::string ScrollBarImage() const;
		void ScrollBallImage(const std::string& imagePath);
		std::string ScrollBallImage() const;

      protected:
        std::string txt;
        std::string _font;
        int size; //!< Font size
        GXColor color; //!< Font color
				
        void EnsureItems();

      private:
        std::vector<Label*> _textItems;
        u32 _nbToDisplay;
		u32 _nbToSkip;
		bool _rebuildVector;
        TrackBar _trackBar;
        void ScrollChanged(Libwiisys::Object* sender, Libwui::Events::TrackBarEventArgs* args);
		void InvalidateLabelVector();
		void RebuildLabelVector(Libwui::Resources::FontResource* resource);
		void ApplyLabelStyles();
		void CheckScrollVisibility();
    };
  }
}
#endif
