#pragma once
#include <GonEngine/memcfg/scp_ptr.hpp>
#include "GonEngine/memcfg/goncfg.h"
// posiblemente borrar-depurar
#include "GonEngine/renderer/api_context.hpp"

namespace Gon
{
	class   Event;
	struct  Position 
	{ 
		float width{ 0.0f };
		float height{ 0.0f }; 
	};

	// window base specifications
	// default values initialization
	struct WProps 
	{
		WProps(const std::string& title = "Gon-Window",
			const API api = API::OpenGL,
			const int32_t w = 1920,
			const int32_t h = 1080)
			: m_title(title),
			m_api(api),
			m_width(w),
			m_height(h),
			m_vsync(true)
		{}
		const std::string m_title;
		const API m_api;
		const int32_t m_width, m_height;
		const bool m_vsync;
	};
	
	// window base class (interface-abstract-multiplatform)
	class SWindow
	{
	public:
		SWindow() = default;
		virtual ~SWindow() = default;

		SWindow(const SWindow&) = delete;
		SWindow& operator=(const SWindow&) = delete;

		SWindow(SWindow&&) noexcept = delete;
		SWindow& operator=(SWindow&&) noexcept = delete;

		virtual void init() = 0;
		virtual void swapBuffers() = 0; // updating
		virtual void* getWindow() const = 0;

		virtual void maximize() = 0;

		virtual int32_t width()	 = 0;
		virtual int32_t height()	 = 0;
		virtual Position getPosition() = 0;		

		virtual void setCallBack(const std::function<void(Event&)>& cb) = 0;

		virtual void setVsync(bool toggle) = 0;
		virtual bool isVsync() const = 0;
		virtual void setCaptureMode(const bool toggle) const = 0;		

		// Importante:
		// Para que fuera completamente independientemente de la plataforma 
		// haria falta algun control o switch (o a nivel de pre-proceso)
		static u_ptr<SWindow> create(const WProps& window_props);
	};
}