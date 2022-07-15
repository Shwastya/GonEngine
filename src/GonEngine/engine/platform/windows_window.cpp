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
	std::unique_ptr<SWindow> SWindow::create(const WProps& data)
	{
		GON_TRACE("unique_ptr for GLFW Window (Win-platform)");
		return std::make_unique<Window>(data);

	}
	//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

	void Window::shutDown()
	{
		
		_GLFW_On = false;
		glfwTerminate();		
		GON_INFO("[DESTROYED] GLFW {0} Window.", m_data.m_title);
	}

	Window::Window(const WProps& window_props)
	{
		m_data.m_title  = window_props.m_title;
		m_data.m_width  = window_props.m_width;
		m_data.m_height = window_props.m_height;

		GON_INFO("[CREATING GLFW {0} Window.", m_data.m_title);
		init();
	}

	Window::~Window()
	{
		GON_INFO("[DESTROYING] GLFW {0} Window.", m_data.m_title);
		shutDown();
	}
	void Window::init()
	{		
		if (!_GLFW_On)
		{
			const int succes = glfwInit();
			glfwSetErrorCallback(GLFWErrorCallback);
			_GLFW_On = true;
		}

		if (m_fullScreen)
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
			m_window = glfwCreateWindow(m_data.m_width, m_data.m_height, m_data.m_title.c_str(), nullptr, nullptr);
		}

		// cambiar esto para abstraer contexto de render 
		//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
		
		glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Queremos OpenGL 3.3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Para hacer feliz a MacOS ; Aunque no debería ser necesaria
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //No queremos el viejo OpenGL 	

		glfwMakeContextCurrent(m_window);    
		int result = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if (!result) GON_ERROR("Error initializing GLAD! {0}:", result);
		//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-


		glfwSetWindowUserPointer(m_window, &m_data);	

		GON_INFO("[CREATED] window {0} {1} {2}", m_data.m_title, m_data.m_width, m_data.m_height);
	}
	// --- init() done <---


	void Window::swapBuffers()
	{		
		
		glfwSwapBuffers(m_window);		
		glfwPollEvents();
	}

	void Window::maximize() { glfwMaximizeWindow(m_window);	}

	uint32_t& Window::width()  { return m_data.m_width; }
	uint32_t& Window::height() { return m_data.m_height; }

	Position Window::getPosition()
	{
		int x, y;
		glfwGetWindowPos(m_window, &x, &y);
		const Position position = { x, y };
		return position; // copy ellision
	}

	void* Window::getWindow() const { return m_window; }

	void Window::setCallBack(const std::function<void(Event&)>& cb)
	{
		m_data.CallBack = cb;
	}

	void Window::setVsync(bool toggle)
	{
		glfwSwapInterval(static_cast<int>(toggle));
		m_data.m_vsync = toggle;
	}

	bool Window::isVsync() const { return m_data.m_vsync; }

	// captura del raton en pantalla
	void Window::setCaptureMode(bool& toggle) const
	{
		if (toggle)	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		else glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	

	
	




}