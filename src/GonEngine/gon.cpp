#include "GonEngine/platform/windows_window.hpp"
#include "GonEngine/events/events.hpp"
#include "GonEngine/input.hpp"
#include "GonEngine/gon.hpp"
#include "GonEngine/log.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace gon {

	GonEngine* GonEngine::s_instance = nullptr;

	GonEngine::GonEngine(const API api, const std::string& name, const int32_t w, 
		const int32_t h, const size_t reserve)
		: m_gon_is_running(true), m_layers(reserve),
		  m_window(SWindow::create({name, api, w, h})),
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
			for (auto& layer : m_layers)
			{
				layer->onUpdate(temporal);
				layer->onRender();
			}
			m_imgui->onRender();
			m_imgui->closeRender();

			m_window->swapBuffers();
		}
	}


	GonEngine& GonEngine::getGon() {		
		return *s_instance;
	}
	double GonEngine::getTime() 
	{
		const double getTime = glfwGetTime();
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
	

	void GonEngine::pushNode(u_ptr<NLayer> node)
	{
		m_layers.pushLayer(std::move(node));
	}


	void GonEngine::pushOverNode(u_ptr<NLayer> overnode)
	{
		m_layers.pushLayer(std::move(overnode));
	}

	
	const bool GonEngine::onCloseWindow()
	{
		m_gon_is_running = false;
		return true;
	}
}