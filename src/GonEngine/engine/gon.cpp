#include "GonEngine/engine/gon.hpp"
#include "GonEngine/engine/platform/windows_window.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace gon {

	
	
	GonEngine::GonEngine(const std::string& name = "Gon Engine")// : m_gonRunning(true)
	{
		m_window = SWindow::create(name);
		m_window->setVsync(true);

		//m_gonRunning = true;




		// Bindeamos las callbacks a la funcion miembro OnEvent()
		//m_window->setCallBack(std::bind(&GonEngine::OnEvent, this, std::placeholders::_1));


	}

	GonEngine::~GonEngine()
	{
	}

	GonEngine& GonEngine::ptr()
	{
		// estudiar si conviene eliminar
		// la opcion singleton del engine
		static GonEngine instance;
		return instance;
	}
	void GonEngine::run()
	{
		while (m_gonRunning)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_window->swapBuffers();
		}
	}
}