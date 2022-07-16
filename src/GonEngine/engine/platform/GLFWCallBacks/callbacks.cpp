
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GonEngine/engine/window.hpp"
#include "GonEngine/engine/events/events.hpp"
#include "GonEngine/engine/platform/GLFWCallBacks/callbacks.hpp"

#define CAST reinterpret_cast<WindowData*>

namespace gon
{
	void WDataCallBacks::init(const WProps& window_props)
	{
		m_data.m_title  = window_props.m_title;
		m_data.m_width  = window_props.m_width;
		m_data.m_height = window_props.m_height;
	}

	WindowData* WDataCallBacks::ptr()
	{
		return &m_data;
	}

	void WDataCallBacks::callBacks(GLFWwindow* w)
	{
		glfwSetWindowUserPointer(w, &m_data);

		// On Window Close
		glfwSetWindowCloseCallback(w, [](GLFWwindow* window)
		{
			auto& data = *(CAST(glfwGetWindowUserPointer(window)));

			OnWindowClose event;
			data.CallBack(event);
		});


		// On Window Resize
		glfwSetWindowSizeCallback(w, [](GLFWwindow* window, int width, int height)
		{
			auto& data = *(CAST(glfwGetWindowUserPointer(window)));

			OnWindowResize event
			(
				static_cast<uint32_t>(width),
				static_cast<uint32_t>(height)
			);
			data.CallBack(event);
			data.m_width  = width;
			data.m_height = height;
		});

		// On Set key
		glfwSetKeyCallback(w, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			auto& data = *(CAST(glfwGetWindowUserPointer(window)));

			switch (action)
			{
				case GLFW_PRESS:
				{
					OnKeyPressed event((KeyCode)key, 0);
					data.CallBack(event);
					break;
				}
				case GLFW_RELEASE:
				{
					OnKeyReleased event((KeyCode)key);
					data.CallBack(event);
					break;
				}
				case GLFW_REPEAT:
				{
					OnKeyPressed event((KeyCode)key, 1);
					data.CallBack(event);
					break;
				}
			}
		});

		// On Set Char
		glfwSetCharCallback(w, [](GLFWwindow* window, uint32_t codepoint)
		{
			auto& data = *(CAST(glfwGetWindowUserPointer(window)));

			OnKeyTyped event((KeyCode)codepoint);
			data.CallBack(event);
		});

		// On Mouse Button
		glfwSetMouseButtonCallback(w, [](GLFWwindow* window, int button, int action, int mods)
		{
			auto& data = *(CAST(glfwGetWindowUserPointer(window)));

			switch (action)
			{
				case GLFW_PRESS:
				{
					OnMouseButtonPressed event(button);
					data.CallBack(event);
					break;
				}
				case GLFW_RELEASE:
				{
					OnMouseButtonReleased event(button);
					data.CallBack(event);
					break;
				}
			}
		});

		// On Mouse Scroll
		glfwSetScrollCallback(w, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			auto& data = *(CAST(glfwGetWindowUserPointer(window)));

			OnMouseScrolled event
			(
				static_cast<float>(xOffset),
				static_cast<float>(yOffset)
			);
			data.CallBack(event);
		});

		// On Set Cursor Position
		glfwSetCursorPosCallback(w, [](GLFWwindow* window, double x, double y)
		{
			auto& data = *(CAST(glfwGetWindowUserPointer(window)));
			OnMouseMoved event
			(
				static_cast<float>(x),
				static_cast<float>(y)
			);
			data.CallBack(event);
		});
	}

}



