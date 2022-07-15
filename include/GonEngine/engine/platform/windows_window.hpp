#pragma once
#include "GonEngine/engine/window.hpp"

typedef struct GLFWwindow GLFWwindow;

namespace gon
{	
	class Window : public SWindow
	{
		void shutDown();

	public:
		Window(const WProps& data);
		virtual ~Window();

		virtual void init() override;
		virtual void swapBuffers() override;

		virtual void maximize() override;

		virtual uint32_t& width()    override;
		virtual uint32_t& height()   override;
		virtual Position getPosition() override;

		virtual void* getWindow() const override;

		virtual void setCallBack(const std::function<void(Event&)>& cb) override;

		virtual void setVsync(bool toggle) override;
		virtual bool isVsync() const override;
		virtual void setCaptureMode(bool& toggle) const override;

	private:
		struct WindowData
		{
			std::string m_title;
			uint32_t m_width, m_height;
			bool m_vsync{true};
			std::function<void(Event&)> CallBack;
		};

		WindowData m_data;
		GLFWwindow* m_window;	
		bool m_fullScreen = false;
	};
	
}