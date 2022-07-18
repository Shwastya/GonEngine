#pragma once
#include <functional>
#include <iostream>

struct GLFWwindow;

namespace gon 
{
	struct WProps; class Event;

	struct WindowData
	{
		std::string m_title;
		uint32_t m_width, m_height;
		bool m_vsync{ true };
		std::function<void(Event&)> CallBack;
	};

	struct WDataCallBacks
	{
	public:

		WDataCallBacks() = default;

		void init(const WProps& window_props);
		const bool isVsync() const { return m_data.m_vsync; }

		WindowData* ptr();

		void callBacks(GLFWwindow* w);

	private:
		
		WindowData m_data;
	};
}