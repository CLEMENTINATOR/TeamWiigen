#ifndef _UI_COMPONENT_TRACKBAR_H_
#define _UI_COMPONENT_TRACKBAR_H_

#include "../Control.hpp"
#include "Button.hpp"
#include "Image.hpp"
#include "../Events/TrackBarEvent.hpp"

#define LeftDefaultImage UpDefaultImage
#define LeftOverImage UpOverImage
#define LeftClickedImage UpClickedImage
#define RightDefaultImage DownDefaultImage
#define RightOverImage DownOverImage
#define RightClickedImage DownClickedImage

namespace Libwui
{
  namespace Component
  {
  	  typedef enum
  	  {
  		TrackBarMode_Horizontal,
  		TrackBarMode_Vertical,
  	  }TrackBarMode;

    class TrackBar : public Control
    {
    	public:
    		TrackBar();
    		virtual ~TrackBar();
    		void InitializeComponents();
    		virtual void ProcessMessage(Message& message);
    		void SetValue(u32 val);
    		u32 GetValue();
    		void SetMinValue(u32 min);
    		u32 GetMinValue();
    		void SetMaxValue(u32 max);
    		u32 GetMaxValue();
    		void SetMode(TrackBarMode mode);
    		TrackBarMode GetMode();
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

    		Events::TrackBarEvent ValueChanged;

    	protected:
    		void EnsureItems();
    		virtual void OnValueChanged();

    	private:
    		Libwui::Component::Button _btnUp;
			Libwui::Component::Button _btnDown;
			Libwui::Component::Image _scrollBar;
			Libwui::Component::Image _scrollBall;
			u32 _minValue;
			u32 _maxValue;
			u32 _value;
			bool _scrollBallDrag;
			bool _scrollBallMoved;
			TrackBarMode _mode;
			bool _modeChanged;

			void btnDown_Clicked(Object* sender, Libwui::Events::CursorEventArgs* args);
			void btnUp_Clicked(Object* sender, Libwui::Events::CursorEventArgs* args);
			void scrollBall_move(Object* sender, Libwui::Events::CursorEventArgs* args);
			void scollBall_held(Object* sender, Libwui::Events::CursorEventArgs* args);
			void scrollBall_release(Object* sender, Libwui::Events::CursorEventArgs* args);
			void DrawUpdate();
    };
  }
}
#endif
