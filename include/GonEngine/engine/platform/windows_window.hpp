#pragma once
#include "GonEngine/engine/window.hpp"
typedef struct GLFWwindow GLFWwindow;

namespace gon
{	class Window : public SWindow
	{
	public:

		Window(const WindowData& data);
		virtual ~Window();

		virtual void init() override;
		virtual void swapBuffers() override;

		virtual void maximize() override;

		virtual uint32_t& width()    override;
		virtual uint32_t& height()   override;
		virtual Position& position() override;

		virtual void* getOriginalWindow() const override;

		virtual void setCallBack(const std::function<void(Event&)>& cb) override;

		virtual void setVsync(bool& toggle) override;
		virtual bool isVsync() const override;
		virtual void setCaptureMode(bool& toggle) const override;

	private:
		WindowData m_data;
		GLFWwindow* m_window;
		
	};
	
}