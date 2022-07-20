#include <Windows.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GonEngine/window.hpp"
#include "GonEngine/events/events.hpp"
#include "GonEngine/renderer/renderer_api.hpp"
#include "GonEngine/platform/OpenGL/opengl_context.hpp"
#include "GonEngine/platform/GLFWCallBacks/callbacks.hpp"
#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/log.hpp"

#pragma warning( disable : 4100 )

namespace gon
{

	static void GLFWErrorCallback(int error, const char* description)
	{
		GON_ERROR("GLFW Error ({0}): {1}", error, description);
		glfwTerminate();
	}

	WDataCallBacks::WDataCallBacks(const WProps& window_props)
		: m_data(window_props.m_title, window_props.m_width, window_props.m_height),
		m_window(nullptr), m_Context(nullptr)

	{
		RendererApi::_API(true, window_props.m_api);
	}	

	void WDataCallBacks::initGLFW()
	{
		glfwInit();
		glfwSetErrorCallback(GLFWErrorCallback);
	}

	void WDataCallBacks::initContext()
	{
		switch (RendererApi::_API())
		{
		case API::OpenGL:
			GON_TRACE("Selected API: OpenGL");
			m_Context = std::make_unique<OpenGLContext>(m_window);
			break;
		case API::DirectX:
			GON_TRACE("Selected API: DirectX");
			GON_WARN("DirectX is not implemented yet. OpenGl will be started instead.");
			m_Context = std::make_unique<OpenGLContext>(m_window);
			break;
		case API::Vulkan:
			GON_TRACE("Selected API: Vulkan");
			GON_WARN("Vulkan is not implemented yet. OpenGl will be started instead.");
			m_Context = std::make_unique<OpenGLContext>(m_window);
			break;
		}

		m_Context->init();
		GON_INFO("[CREATED] window '{0}' {1} {2}", m_data.m_title, m_data.m_width, m_data.m_height);
	}	

	void WDataCallBacks::initFullScreenWindow()
	{
		// NOTAS GLFW Oficial Site:
		 
		// glfwGetPrimaryMonitor()						-> devuelve el monitor primario 
		// GLFWmonitor									-> opaque monitor object
		// GLFWmonitor** glfwGetMonitors(int* count)	-> array de monitores conectados
	
		GLFWmonitor* PrimaryMonitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* m = glfwGetVideoMode(PrimaryMonitor);

		m_window = glfwCreateWindow
		(
			m->width, 
			m->height,
			m_data.m_title.c_str(), 
			PrimaryMonitor, NULL
		);
	}
	void WDataCallBacks::initWindowedWindow()
	{
		m_window = glfwCreateWindow(m_data.m_width,
			m_data.m_height, m_data.m_title.c_str(),
			NULL, NULL);
	}

	void* WDataCallBacks::getWindow() { return m_window; }

	void WDataCallBacks::swapBuffers()
	{		
		m_Context->swapBuffers();
		glfwPollEvents();
	}

	void WDataCallBacks::maximize()	{ glfwMaximizeWindow(m_window);	}	

	#define CAST reinterpret_cast<WindowData*>

	void WDataCallBacks::initCallBacks()
	{
		glfwSetWindowUserPointer(m_window, &m_data);

		// On Window Close
		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
		{
			auto& data = *(CAST(glfwGetWindowUserPointer(window)));
			OnWindowClose event;
			data.CallBack(event);
		});

		// On Window Resize
		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
		{
			auto& data = *(CAST(glfwGetWindowUserPointer(window)));
			OnWindowResize event
			(
				static_cast<int32_t>(width),
				static_cast<int32_t>(height)
			);
			data.CallBack(event);
			data.m_width  = width;
			data.m_height = height;
		});

		// On Set key
		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
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
		glfwSetCharCallback(m_window, [](GLFWwindow* window, uint32_t codepoint)
		{
			auto& data = *(CAST(glfwGetWindowUserPointer(window)));
			OnKeyTyped event((KeyCode)codepoint);
			data.CallBack(event);
		});

		// On Mouse Button
		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods)
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
		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset)
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
		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double x, double y)
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

	void WDataCallBacks::callBack(const std::function<void(Event&)>& cb)
	{
		m_data.CallBack = cb ;
	}

	int32_t WDataCallBacks::getWidth() { return m_data.m_width; }
	int32_t WDataCallBacks::getHeight() { return m_data.m_height; }
	std::pair<float, float> WDataCallBacks::getPosition()
	{
		int x, y;
		glfwGetWindowPos(m_window, &x, &y);
		const auto position
		{
			std::make_pair
			(
				static_cast<float>(x),
				static_cast<float>(y)
			)
		};		
		return position;
	}

	void WDataCallBacks::setVsync(const bool toggle)
	{
		glfwSwapInterval(static_cast<int>(toggle));
		m_data.m_vsync = toggle;
	}

	void WDataCallBacks::setCapturemode(const bool toggle)
	{
		if (toggle)	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		else glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	const bool WDataCallBacks::isVsync() const { return m_data.m_vsync; }

	void WDataCallBacks::shutDown()	
	{ 
		glfwDestroyWindow(m_window);
		glfwTerminate(); 
	}
}



