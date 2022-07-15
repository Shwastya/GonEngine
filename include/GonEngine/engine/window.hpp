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
	
	
	// window base class (interface-abstract-multiplatform)
	class SWindow
	{
	public:
		virtual ~SWindow() = default;

		virtual void init() = 0;
		virtual void swapBuffers() = 0; // updating

		virtual void maximize() = 0;

		virtual uint32_t& width()	 = 0;
		virtual uint32_t& height()	 = 0;
		virtual Position getPosition() = 0;

		virtual void* getWindow() const = 0;

		virtual void setCallBack(const std::function<void(Event&)>& cb) = 0;

		virtual void setVsync(bool toggle) = 0;
		virtual bool isVsync() const = 0;
		virtual void setCaptureMode(bool& toggle) const = 0;		

		struct WProps // non virtual
		{
			WProps(const std::string& title = "Gon-Window", 
				const uint32_t w = 1920, 
				const uint32_t h = 1080)
				: m_title(title),
				m_width(w),
				m_height(h),
				m_vsync(true)
			{}
			const std::string m_title;
			const uint32_t m_width, m_height;
			const bool m_vsync;
		};

		// NOTA:
		// Para que fuera completamente independientemente de la plataforma 
		// haria falta algun control o switch (o a nivel de pre-proceso)
		static std::unique_ptr<SWindow> create(const WProps& window_props);
	};
}