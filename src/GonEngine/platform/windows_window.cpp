#include "GonEngine/platform/windows_window.hpp"
#include "GonEngine/memcfg/scp_ptr.hpp"
#include "GonEngine/events/events.hpp"
#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/log.hpp"

namespace Gon {	

	//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
	u_ptr<SWindow> SWindow::create(const WProps& data)
	{		
		return std::make_unique<Window>(data);
	}
	//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

	static bool _GLFW_On = false;

	Window::Window(const WProps& window_props)
		:m_windowHandler(std::make_unique<WindowHandler>(window_props))
	{
		init();
	}
	Window::~Window()
	{
		m_windowHandler->shutDown();
		GON_TRACE("[DESTROYED] GLFW '{0}' Window.", m_windowHandler->getTitle());
	}
	void Window::init()
	{
		if (!_GLFW_On) {
			m_windowHandler->initGLFW();
			_GLFW_On = true;
		}
		if (m_fullScreen) {
			GON_TRACE("Initializing GLFW fullscreen mode...");
			m_windowHandler->initFullScreenWindow();
		}
		else {
			GON_TRACE("Initializing GLFW windowed mode...");
			m_windowHandler->initWindowedWindow();
		}		
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
	int32_t Window::width()			{ return m_windowHandler->getHeight(); }
	int32_t Window::height()		{ return m_windowHandler->getWidth(); }
	Position Window::getPosition()
	{
		auto [x, y] = m_windowHandler->getPosition();
		return { x, y };
	}
	void Window::setVsync(bool toggle)	{ m_windowHandler->setVsync(toggle); }
	bool Window::isVsync() const		{ return m_windowHandler->isVsync(); }
	void Window::setCaptureMode(bool& toggle) const	{ m_windowHandler->setCapturemode(toggle);}
}
	




