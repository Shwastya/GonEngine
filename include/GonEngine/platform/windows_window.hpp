#pragma once
#include "GonEngine/window.hpp"
#include "GonEngine/platform/window_handler/window_handler.hpp"

namespace Gon {

	class RendererContext;
	class Window : public SWindow
	{
	public:
		Window(const WProps& window_props);
		virtual ~Window();

		virtual void init()				override;
		virtual void swapBuffers()		override;

		virtual void maximize()			override;

		virtual int32_t width()			override;
		virtual int32_t height()		override;
		virtual Position getPosition()	override;

		virtual void* getWindow() const override;
		virtual void setCallBack(const std::function<void(Event&)>& cb) override;

		virtual void setVsync(bool toggle)				override;
		virtual bool isVsync()					  const override;
		virtual void setCaptureMode(const bool toggle) const override;

	private:		
		u_ptr<WindowHandler> m_windowHandler;
		bool m_fullScreen = false;
	};
	
}