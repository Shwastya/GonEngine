#pragma once
#include "GonEngine/window.hpp"
#include "GonEngine/platform/GLFWCallBacks/callbacks.hpp"


namespace gon
{
	class RendererContext;
	class Window : public SWindow
	{
		//void shutDown();

	public:
		Window(const WProps& window_props);
		virtual ~Window();

		virtual void init()				override;
		virtual void swapBuffers()		override;

		virtual void maximize()			override;

		virtual int32_t width()		override;
		virtual int32_t height()		override;
		virtual Position getPosition()	override;

		virtual void* getWindow() const override;

		virtual void setCallBack(const std::function<void(Event&)>& cb) override;

		virtual void setVsync(bool toggle) override;
		virtual bool isVsync() const override;
		virtual void setCaptureMode(bool& toggle) const override;

	private:

		
		u_ptr<WDataCallBacks> m_data; // windows scoped and data
		//GLFWwindow* m_window;
		//u_ptr<RendererContext> m_context;
		bool m_fullScreen = false;
	};
	
}