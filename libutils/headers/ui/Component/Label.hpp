#ifndef _UI_COMPONENT_LABEL_H_
#define _UI_COMPONENT_LABEL_H_

#include "../Control.hpp"
#include <string>

namespace UI
{
	namespace Component
	{		
		class Label : public Control
		{
			public:
				Label(const std::string& text, int s = 12, GXColor c = (GXColor){255, 255, 255, 255});
				
				virtual void ProcessMessage(Message& message);
				
				void Text(const std::string& text);
				void FontSize(int size);
				void ForeColor(GXColor c);
				void Style(u16 s);
				void SetTextAlignment(HAlign hor, VAlign vert);
				void Draw();
				
			protected:
				std::string txt;
				int size; //!< Font size
				GXColor color; //!< Font color
				int textScrollPos; //!< Current starting index of text string for scrolling
				bool scrollToRight;
				int textScrollInitialDelay; //!< Delay to wait before starting to scroll
				int textScrollDelay; //!< Scrolling speed
				u16 style; //!< FreeTypeGX style attributes
		};
	}
}

#endif
