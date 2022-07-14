#pragma once
#include "GonEngine/engine/window.hpp"


namespace gon
{
	typedef struct GLFWwindow GLFWwindow;

	class Window : public SWindow
	{

		Window(const WindowData& data);
		virtual ~Window();

		virtual void init() override;




	protected:
		WindowData m_data;
		glm::vec2 test;
	};
	
}