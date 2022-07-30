#include "GonEngine/renderer/management/camera_manager.hpp"
#include "GonEngine/renderer/management/render_manager.hpp"
#include "GonEngine/platform/OpenGL/opengl_shader.hpp"
#include "GonEngine/platform/OpenGL/opengl_vao.hpp"
#include "GonEngine/renderer/renderer.hpp"
#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/log.hpp"

namespace Gon {
	SceneRenderer::SceneRenderer()
		: m_render(std::make_unique<RenderManager>()),
		  m_data(std::make_unique<MatrixData>())
			
	{
		GON_TRACE("[CREATED] Scene Renderer.");
	}
	SceneRenderer::~SceneRenderer()
	{
		GON_TRACE("[DESTROYED] Scene Renderer.");
	}
	void SceneRenderer::shareCam(const s_ptr<CameraMan>& cameraman)
	{
		m_cameraMan = cameraman;
	}
	void SceneRenderer::InitConfiguration(const bool cullface, const bool depthtest, const bool alphablending)
	{
		m_render->initConfig(cullface, depthtest, alphablending);
	}

	void SceneRenderer::begin(const s_ptr<Camera>& camera)
	{		
		m_data->View		= camera->getViewMatrix();
		m_data->Projection	= camera->getProjectionMatrix();

		m_render->setClearColor({ 0.15f, 0.15f, 0.15f, 1.0f });
		m_render->clear();
	}

	void SceneRenderer::begin()
	{
		m_render->setClearColor({ 0.15f, 0.15f, 0.15f, 1.0f });
		m_render->clear();
	}

	void SceneRenderer::end()
	{
		
	}
	void SceneRenderer::submit(const VAO* vao, const Shader* shader, const glm::mat4& model)
	{

		shader->bind();
		shader->uniform("uModel",	model);
		/*shader->uniform("uView", m_data->View);
		shader->uniform("uProj", m_data->Projection);*/
		shader->uniform("uView", m_cameraMan->getCam()->getViewMatrix());
		shader->uniform("uProj", m_cameraMan->getCam()->getProjectionMatrix());

		vao->bind();
		m_render->Draw(vao);
	}
}