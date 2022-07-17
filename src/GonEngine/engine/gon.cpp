#include "GonEngine/engine/platform/windows_window.hpp"
#include "GonEngine/engine/gon.hpp"
#include "GonEngine/engine/log.hpp"
#include "GonEngine/goncfg.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GonEngine/engine/input.hpp"

namespace gon {

	GonEngine* GonEngine::s_instance = nullptr;

	GonEngine::GonEngine(const std::string& name = "Gon Engine", const size_t reserve)
		: m_gon_is_running(true), m_nodes(reserve)
	{
		s_instance = this;
		m_window = SWindow::create(name);
		m_window->setVsync(true);		
		//Bindeamos las callbacks a la funcion miembro OnEvent()
		m_window->setCallBack(std::bind(&GonEngine::onEvent, this, std::placeholders::_1));
	}

	GonEngine::~GonEngine()
	{

	}

	void GonEngine::run()
	{
		while (m_gon_is_running)
		{
			glClearColor(0.5f, 0.0f, 0.4f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			m_window->swapBuffers();

			TimeStep temporal = 0.0f;

			

			for (std::unique_ptr<Node>& node : m_nodes)
			{
				node->onUpdate(temporal);
			}
		}
	}

	GonEngine* GonEngine::getGon() {		
		return s_instance;
	}
	float GonEngine::getTime() {
		const float getTime = glfwGetTime();
		return getTime;
	}
	SWindow* GonEngine::getWindow()
	{
		return m_window.get();
	}



	void GonEngine::onEvent(Event& e)
	{
		
		if (e.getEventType() == EventType::WindowClose)
		{
			onCloseWindow();;
		}				

		for (auto it = m_nodes.end(); it != m_nodes.begin();)
		{
			(*--it)->onEvent(e);			

			if ((*it)->type() == NodeType::Engine)
			{
				
				if (e.getEventType() == EventType::MouseButtonPressed)
				{
					/*GON_ERROR("node Ids: {0}", (*it)->getId());
					GON_WARN("{0}", (*it)->getName());*/
				}
			}
		}
	}

	

	void GonEngine::pushNode(std::unique_ptr<Node> node)
	{
		m_nodes.pushNode(std::move(node));
	}

	void GonEngine::pushOverNode(std::unique_ptr<Node> overnode)
	{
		m_nodes.pushNode(std::move(overnode));
	}
	
	/*const bool GonEngine::onWindowClose(const OnWindowClose& e)
	{
		m_gonRunning = false;
		return true;
	}*/
	const bool GonEngine::onCloseWindow()
	{
		m_gon_is_running = false;
		return true;
	}
}