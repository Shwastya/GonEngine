#pragma once
#include "GonEngine/renderer/api_context.hpp"
#include <functional>
#include <iostream>

struct GLFWwindow;

namespace Gon {

	enum class API;	class Event; struct WProps;

	class WindowHandler
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

		WindowHandler(const WProps& window_props);
		~WindowHandler() = default;

		WindowHandler(const WindowHandler&) = delete;
		WindowHandler& operator=(const WindowHandler&) = delete;

		WindowHandler(WindowHandler&&) noexcept = delete;
		WindowHandler& operator=(WindowHandler&&) noexcept = delete;

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
		u_ptr<APIContext> m_Context;
	};
}