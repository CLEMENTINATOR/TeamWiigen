#ifndef _TEXT_AERA_H_
#define _TEXT_AERA_H_

#include "../Control.hpp"
#include "Label.hpp"

namespace Libwui
{
  namespace Component
  {
	class TextAera : public Control
	{
	public:
		TextAera(const std::string& text, int s = 12, GXColor c = (GXColor){255, 255, 255, 255});
		~TextAera();
		
		virtual void ProcessMessage(Message& message);
		
		virtual void SetSize(int w, int h);
		
		void Text(const std::string& text);
		void SetFont(const std::string& font);
		void FontSize(int size);
		void ForeColor(GXColor c);
		void Draw();
		
	protected:
		std::string txt;
		std::string _font;
		int size; //!< Font size
		GXColor color; //!< Font color
		
	private:
		bool _invalidated;
		void Invalidate();
		void EnsureItems();
		std::vector<Label*> _textItems;
	};
  }
}
#endif
