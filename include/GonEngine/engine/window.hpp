#pragma once
#include <functional>
#include <iostream>

namespace gon
{
	class   Event;
	struct  Position 
	{ 
		float width{ 0.0f };
		float height{ 0.0f }; 
	};
	// window base specifications
	struct WindowData
	{
		WindowData(const std::string& title = "Gon-Window", const uint32_t w = 1920, const uint32_t h = 1080)
			: m_title(title),
			m_width(w),
			m_height(h),
			m_fullScreen(false),
			m_vsync(true)
		{}

		std::string m_title;
		uint32_t m_width;
		uint32_t m_height;
		bool m_fullScreen;
		bool m_vsync;
		std::function<void(Event&)> CallBack;
	};
	
	// window base class (interface-abstract-multiplatform)
	struct SWindow
	{
		virtual ~SWindow() = default;

		virtual void init() = 0;
		virtual void swapBuffers() = 0; // updating

		virtual void maximize() = 0;

		virtual uint32_t& width()	 = 0;
		virtual uint32_t& height()	 = 0;
		virtual Position& position() = 0;

		virtual void* getOriginalWindow() const = 0;

		virtual void setCallBack(const std::function<void(Event&)>& cb) = 0;

		virtual void setVsync(bool& toggle) = 0;
		virtual bool isVsync() const = 0;
		virtual void setCaptureMode(bool& toggle) const = 0;
		
		// NOTA:
		// Para que fuera completamente independientemente de la plataforma 
		// haria falta un  algun control o switch (o a nivel de pre-proceso)
		static std::unique_ptr<SWindow> create(const WindowData& data);	
	};
}