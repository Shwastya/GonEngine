#include "GonEngine/engine/platform/windows_window.hpp"
#include "GonEngine/engine/input.hpp"
#include "GonEngine/engine/gon.hpp"
#include "GonEngine/engine/log.hpp"
#include "GonEngine/goncfg.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace gon {

	GonEngine* GonEngine::s_instance = nullptr;

	GonEngine::GonEngine(const std::string& name, const size_t reserve)
		: m_gon_is_running(true), m_layers(reserve),
		  m_window(SWindow::create(name)),
		  m_imgui(new ImGuiNode(NodeType::ImGui))		
	{
		s_instance = this;
		m_window->setVsync(true);	
		m_imgui->onJoin();

		//Bindeamos las callbacks a la funcion miembro OnEvent()
		m_window->setCallBack(std::bind(&GonEngine::onEvent, this, std::placeholders::_1));
	}

	GonEngine::~GonEngine()
	{
		m_imgui->onQuit();
	}

	void GonEngine::run()
	{
		while (m_gon_is_running)
		{
			glClearColor(0.5f, 0.0f, 0.4f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			

			TimeStep temporal = 0.0f;

			m_imgui->beginRender();
			for (NLayer* node : m_layers)
			{
				node->onUpdate(temporal);				
				node->onRender();
			}
			m_imgui->onRender();
			m_imgui->closeRender();
		

			// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
			//m_imgui_UI->header();
			//for (Node* node : m_nodes)
			//{
				//node->onImguiRender();
			//}
			//m_imgui_UI->footer();
			// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

			m_window->swapBuffers();
		}
	}

	GonEngine& GonEngine::getGon() {		
		return *s_instance;
	}
	float GonEngine::getTime() {
		const float getTime = glfwGetTime();
		return getTime;
	}
	SWindow& GonEngine::getPtrWindow()
	{
		return *m_window;
	}



	void GonEngine::onEvent(Event& e)
	{
		
		if (e.getEventType() == EventType::WindowClose)
		{
			onCloseWindow();;
		}				

		for (auto it = m_layers.end(); it != m_layers.begin();)
		{			
			(*--it)->onEvent(e);
		}
	}

	

	void GonEngine::pushNode(NLayer *node)
	{
		m_layers.pushLayer(node);
	}

	void GonEngine::pushOverNode(NLayer* overnode)
	{
		m_layers.pushLayer(overnode);
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