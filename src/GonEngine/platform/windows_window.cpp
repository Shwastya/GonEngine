#include "GonEngine/platform/windows_window.hpp"
#include "GonEngine/events/events.hpp"
#include "GonEngine/log.hpp"
#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/memcfg/scp_ptr.hpp"


namespace gon
{
	static bool _GLFW_On = false;
	
	//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
	u_ptr<SWindow> SWindow::create(const WProps& data)
	{
		GON_TRACE("unique_ptr for GLFW Window (Win-platform)");
		
		return std::make_unique<Window>(data);
	}
	//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
	
	Window::Window(const WProps& window_props)
		:m_data(std::make_unique<WDataCallBacks>(window_props))
	{
		GON_INFO("[CREATING] GLFW '{0}' Window.", window_props.m_title);
		init();
	}
	Window::~Window()
	{
		GON_INFO("[DESTROYING] GLFW '{0}' Window.", m_data->getTitle());
		m_data->shutDown();
		GON_INFO("[DESTROYED] GLFW '{0}' Window.", m_data->getTitle());
	}
	void Window::init()
	{
		if (!_GLFW_On)
		{
			m_data->initGLFW();
			_GLFW_On = true;
		}
		if (m_fullScreen)
		{
			GON_TRACE("Initializing GLFW fullscreen mode");
			m_data->initFullScreenWindow();
		}
		else
		{
			GON_TRACE("Initializing GLFW windowed mode");
			m_data->initWindowedWindow();
		}


		//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
		m_data->initContext();
		//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

		m_data->initCallBacks();
		
	}

	void Window::swapBuffers()
	{		
		m_data->swapBuffers();
	}
	void* Window::getWindow() const
	{
		return m_data->getWindow();
	}
	void Window::maximize()
	{
		m_data->maximize();
	}		

	void Window::setCallBack(const std::function<void(Event&)>& cb)
	{
		m_data->callBack(cb);
	}

	int32_t Window::width()
	{
		return m_data->getHeight();
	}

	int32_t Window::height()
	{
		return m_data->getWidth();
	}

	Position Window::getPosition()
	{
		auto [x, y] = m_data->getPosition();
		return { x, y };
	}

	void Window::setVsync(bool toggle)
	{
		m_data->setVsync(toggle);
	}

	bool Window::isVsync() const 
	{ 
		return m_data->isVsync(); 
	}
	
	void Window::setCaptureMode(bool& toggle) const
	{
		// captura del raton en pantalla
		m_data->setCapturemode(toggle);
	}
}
	




