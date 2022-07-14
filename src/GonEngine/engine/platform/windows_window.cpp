#include "GonEngine/engine/platform/windows_window.hpp"
#include "GonEngine/engine/log.hpp"
#include "GonEngine/goncfg.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace gon
{
	static bool _GLFW_On = false;
	static void GLFWErrorCallback(int error, const char* description)
	{
		GON_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
	extern std::unique_ptr<SWindow> create(const WindowData data) 
	{
		GON_TRACE("Instantiating GLFW Windows-platform with unique_ptr");
		return std::make_unique<Window>(data); 
	}
	//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

	Window::Window(const WindowData& data)
		: m_data(data)
	{
		init();
	}

	Window::~Window()
	{
	}
	void Window::init()
	{
		GON_TRACE("Created window {0} {1} {2}", m_data.m_title, m_data.m_width,
			m_data.m_height);

		if (!_GLFW_On)
		{
			const int succes = glfwInit();
			glfwSetErrorCallback(GLFWErrorCallback);
			_GLFW_On = true;
		}

		if (m_data.m_fullScreen)
		{
			// NOTAS GLFW Oficial Site:
			// 
			// glfwGetPrimaryMonitor() 
			//		-> devuelve el monitor primario 
			// GLFWmonitor 
			//		-> opaque monitor object
			// GLFWmonitor** glfwGetMonitors(int* count)  
			//		-> array de monitores conectados
			//
			GON_TRACE("Initializing GLFW fullscreen mode");

			GLFWmonitor* PrimaryMonitor = glfwGetPrimaryMonitor();
			const GLFWvidmode* m = glfwGetVideoMode(PrimaryMonitor);

			m_window = glfwCreateWindow(m->width, m->height, 
				m_data.m_title.c_str(), PrimaryMonitor, nullptr);
		}
		else
		{
			GON_TRACE("Initializing GLFW windowed mode");

			m_window = glfwCreateWindow(m_data.m_width, m_data.m_height,
				m_data.m_title.c_str(), nullptr, nullptr);
		}

		// cambiar esto para abstraer contexto de render 
		//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4.1);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4.1);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);			

		glfwMakeContextCurrent(m_window);    
		int result = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-


		glfwSetWindowUserPointer(m_window, &m_data);		
	}
	// --- init() done ---


	void Window::swapBuffers()
	{		
		glfwSwapBuffers(m_window);		
	}

	void Window::maximize() { glfwMaximizeWindow(m_window);	}

	uint32_t& Window::width() { return m_data.m_width; }
	uint32_t& Window::height() { return m_data.m_height; }

	Position& Window::position()
	{
		// TODO: Insertar una instrucción "return" aquí
	}




}