#pragma once
#include <functional>
#include <iostream>
#include "GonEngine/renderer/renderer_context.hpp"
struct GLFWwindow;

namespace gon 
{
	class Event;
	struct WProps; 
	enum class API;	

	class WDataCallBacks
	{
	private:
		struct WindowData
		{
			WindowData(const std::string& title = "noname", const int32_t w = 0, const int32_t h = 0) 
			: m_title(title), m_width(w), m_height(h) {}
			std::string m_title;
			int32_t m_width;
			int32_t m_height;
			bool m_vsync{ true };
			std::function<void(Event&)> CallBack;
		};

	public:

		WDataCallBacks(const WProps& window_props);
		~WDataCallBacks() = default;

		WDataCallBacks(const WDataCallBacks&) = delete;
		WDataCallBacks& operator=(const WDataCallBacks&) = delete;

		WDataCallBacks(WDataCallBacks&&) noexcept = delete;
		WDataCallBacks& operator=(WDataCallBacks&&) noexcept = delete;

		void initGLFW();
		void initContext();
		void initFullScreenWindow();
		void initWindowedWindow();

		void* getWindow();
		void swapBuffers();

		void maximize();
		
		void initCallBacks();
		void callBack(const std::function<void(Event&)>& cb);		

		int32_t getWidth();
		int32_t getHeight();
		std::pair<float, float> getPosition();

		const std::string& getTitle() { return m_data.m_title; }

		void setVsync(const bool toggle);
		const bool isVsync() const;
		void setCapturemode(const bool toggle);
		
		void shutDown();		

	private:		
		WindowData m_data;
		GLFWwindow* m_window;	
		u_ptr<RendererContext> m_Context;
	};
}