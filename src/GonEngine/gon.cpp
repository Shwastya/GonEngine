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
#include <GLFW/glfw3.h>

#include "GonEngine/renderer/camera/c_orthographic.hpp"
#include "GonEngine/renderer/camera/c_perspective.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace gon {

	const std::string k_vs = ("../assets/shaders/basic_vertex.vs");
	const std::string k_fs = ("../assets/shaders/basic_fragment.fs");

	GonEngine* GonEngine::s_instance = nullptr;

	GonEngine::GonEngine
	(
		const API api = API::OpenGL,
		const std::string& name = "Gon Engine",
		const int32_t width = 1920,
		const int32_t height = 1080,
		const size_t reserve = k_default_reserve
	)
		: m_gon_is_running(true),
		m_layers(std::make_unique<NLayersManager>(reserve)),
		m_window(SWindow::create({ name, api, width, height })),
		m_imgui(std::make_unique<ImguiLayerContext>()),
		m_vao{ VAO::create(2) },
		m_render(std::make_unique<RenderManager>())	
	{
		s_instance = this;
		m_window->setVsync(true);		
		m_imgui->onJoin();

		//Bindeamos las callbacks a la funcion -> GonEngine::OnEvent()
		m_window->setCallBack(std::bind(&GonEngine::onEvent, this, std::placeholders::_1));	

		Triangle triangle;
		
		u_ptr<VBO> vbo{ VBO::create(triangle.get(),  triangle.size())};
		VBOLayout bufferLayout =
		{
			{DataType::Float3, "aPos"},
			{DataType::Float2, "aUvs"},
			{DataType::Float3, "aNormal"},
			{DataType::Float3, "aTang"},
			{DataType::Float3, "aBitang"},			
		};
		vbo->setLayout(bufferLayout);
		m_vao->takeVBO(vbo);


		float vertexColor[3 * 3]
		{
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f
		};
		u_ptr<VBO> vbo2{ VBO::create(vertexColor, sizeof(vertexColor)) };
		VBOLayout bufferLayout2
		{
			{{DataType::Float3, "aColor"},}
		};
		vbo2->setLayout(bufferLayout2);
		m_vao->takeVBO(vbo2);


		u_ptr<EBO> ebo{ EBO::create(triangle.getIndices(), triangle.nIndices())};
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

			const float dance = static_cast<float>(glm::abs(glm::cos(getTime())));

			glm::mat4 model{ 1.0f };
			
			//model = glm::translate	(model, glm::vec3(0.0f, -1.0f, 0.0f));
			//model = glm::rotate		(model, (float)getTime() * glm::radians(90.0f ) , glm::vec3(0.0f, 0.0f, 1.0f));			
			//model = glm::scale		(model, glm::vec3(1.5f, 1.5f, 1.5f));

			
		
			const auto [view, proj] { m_cameraMan.getViewProjectionMatrix() };
			m_shader->uniform("uModel", model);
			m_shader->uniform("uView", view);
			m_shader->uniform("uProj", proj);

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
		const double getTime{ glfwGetTime() };
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


		if (e.getEventType() == EventType::KeyPressed)
		{
			OnKeyPressed& _e = dynamic_cast<OnKeyPressed&>(e);

			if (_e.getKeyCode() == GON_KEY_C)
			{
				if (m_cameraMan.getCamMode() != CamMode::Ortho)				
					m_cameraMan.switchCam(CamMode::Ortho);				
				else m_cameraMan.switchCam(CamMode::Persp);
			}
			if (_e.getKeyCode() == GON_KEY_R)
			{				
				if (m_cameraMan.getCamMode() != CamMode::Ortho)
					GON_ERROR("No hay camara ortografica activa");
				else m_cameraMan.setRotation(45.0f);
			}
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