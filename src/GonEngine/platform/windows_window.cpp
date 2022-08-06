#include "GonEngine/platform/windows_window.hpp"
#include "GonEngine/memcfg/scp_ptr.hpp"
#include "GonEngine/events/events.hpp"
#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/log.hpp"

namespace Gon {	

	//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
	u_ptr<SWindow> SWindow::create(const WProps& data)
	{		
		return make_u_ptr<Window>(data);
	}
	//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

	static bool _GLFW_On = false;

	Window::Window(const WProps& window_props)
		:m_windowHandler(make_u_ptr<WindowHandler>(window_props))
	{
		init();
	}
	Window::~Window()
	{
		m_windowHandler->shutDown();
		GON_TRACE("[DESTROYED] GLFW '{0}' Window", m_windowHandler->getTitle());
	}
	void Window::init()
	{
		if (!_GLFW_On) {
			m_windowHandler->initGLFW();
			_GLFW_On = true;
		}
		if (m_fullScreen) m_windowHandler->initFullScreenWindow();		
		else m_windowHandler->initWindowedWindow();


		//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
		m_windowHandler->initContext();
		//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
		m_windowHandler->initCallBacks();
		//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
		
	}
	void Window::swapBuffers()		{ m_windowHandler->swapBuffers(); }
	void* Window::getWindow() const	{ return m_windowHandler->getWindow(); }
	void Window::maximize()			{ m_windowHandler->maximize(); }

	void Window::setCallBack(const std::function<void(Event&)>& cb)
	{
		m_windowHandler->callBack(cb);
	}
	int32_t Window::width()			{ return m_windowHandler->getWidth(); }
	int32_t Window::height()		{ return m_windowHandler->getHeight(); }
	Position Window::getPosition()
	{
		auto [x, y] = m_windowHandler->getPosition();
		return { x, y };
	}
	void Window::setVsync(bool toggle)	{ m_windowHandler->setVsync(toggle); }
	bool Window::isVsync() const		{ return m_windowHandler->isVsync(); }
	void Window::setCaptureMode(const bool toggle) const	{ m_windowHandler->setCapturemode(toggle);}
	void Window::enableFullScreenWindow()
	{
		m_windowHandler->fullScreenMode();
	}

	void Window::enableWindowedWindow()
	{
		m_windowHandler->windowedMode();
	}

}
	




