#include "GonEngine/platform/OpenGL/opengl_shader.hpp"
#include "GonEngine/imguimods/imgui_config_layer.hpp"
#include "GonEngine/platform/OpenGL/opengl_vao.hpp"
#include "GonEngine/platform/windows_window.hpp"
#include "GonEngine/renderer/render_manager.hpp"
#include "GonEngine/renderer/api_context.hpp"
#include "GonEngine/geometries/triangle.hpp"
#include "GonEngine/events/events.hpp"
#include "GonEngine/nodes/nodes.hpp"
#include "GonEngine/input.hpp"
#include "GonEngine/gon.hpp"
#include "GonEngine/log.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace gon {

	const std::string k_vs = ("../assets/shaders/basic_vertex.vs");
	const std::string k_fs = ("../assets/shaders/basic_fragment.fs");

	GonEngine* GonEngine::s_instance = nullptr;

	GonEngine::GonEngine
	(
		const API api = API::OpenGL, 
		const std::string& name = "Gon Engine", 		
		const int32_t width  = 1920, 
		const int32_t height = 1080, 
		const size_t reserve = k_default_reserve
	)
		: m_gon_is_running(true),
		  m_layers(std::make_unique<NLayersManager>(reserve)),
		  m_window(SWindow::create({ name, api, width, height })),
		  m_imgui(std::make_unique<ImguiLayerSet>()),
		  m_vao{VAO::create(5)},
		  m_render{std::make_unique<RenderManager>()}
	{
		s_instance = this;
		m_window->setVsync(true);		
		m_imgui->onJoin();

		//Bindeamos las callbacks a la funcion -> GonEngine::OnEvent()
		m_window->setCallBack(std::bind(&GonEngine::onEvent, this, std::placeholders::_1));	
		
		Triangle triangle;						
		u_ptr<VBO> vbo{ VBO::create(triangle.get(), triangle.size()) };
		VBOLayout bufferLayout =
		{
			{DataType::Float3, "aPos", false},
		};
		vbo->setLayout(bufferLayout);
		m_vao->takeVBO(vbo);
		u_ptr<EBO> ebo{ EBO::create(triangle.getIndices(), triangle.nIndices()) };
		m_vao->takeEBO(ebo);
		m_shader = Shader::create(k_vs, k_fs);
	}

	GonEngine::~GonEngine()
	{
		GON_WARN("Shutting down Gon-Engine.");
	}

	void GonEngine::run()
	{
		while (m_gon_is_running)
		{
			m_shader->bind();
			m_vao->bind();

			m_render->setClearColor({ 0.15f, 0.15f, 0.45f, 1.0f });
			m_render->clear();			
			m_render->Draw(m_vao.get());
			

			TimeStep temporal = 0.0f;

			m_imgui->ImguiBegin();
			for (auto& layer : (*m_layers))
			{
				layer->onUpdate(temporal);
				layer->onRender();
			}
			m_imgui->ImguiEnd();


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

		for (auto it = (*m_layers).end(); it != (*m_layers).begin();)
		{			
			(*--it)->onEvent(e);
		}
	}
	

	void GonEngine::pushNode(u_ptr<Node> node)
	{
		m_layers->pushLayer(std::move(node));
	}


	void GonEngine::pushOverNode(u_ptr<Node> overnode)
	{
		m_layers->pushLayer(std::move(overnode));
	}



	
	const bool GonEngine::onCloseWindow()
	{
		m_gon_is_running = false;
		return true;
	}
}