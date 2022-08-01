#include "GonEngine/platform/OpenGL/opengl_renderer_api.hpp"
#include "GonEngine/renderer/management/render_manager.hpp"
#include "GonEngine/renderer/api_context.hpp"
#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/log.hpp"

namespace Gon {

	RenderManager::RenderManager() : m_renderer_api(nullptr)
	{
		GON_TRACE("[CREATED] Renderer Manager.");

		switch (APIContext::getAPI()) 
		{
		case API::None:			
			GON_ASSERT(false, "Not renderer API selected.");
			break;
		case API::OpenGL:
			m_renderer_api = std::make_unique<OpenGLRendererAPI>();
			break;
		case API::DirectX:
			GON_WARN("DirectX not implemented. OpenGL renderer by default");
			m_renderer_api = std::make_unique<OpenGLRendererAPI>();
			break;
		case API::Vulkan:
			GON_WARN("Vulkan not implemented. OpenGL renderer by default");
			m_renderer_api = std::make_unique<OpenGLRendererAPI>();
			break;
		default:
			GON_ASSERT(false, "Unknown renderer API.");
			break;
		}
		m_renderer_api->initConfig(); // default init configuration
	}
	RenderManager::~RenderManager()	{ GON_TRACE("[DESTROYED] Renderer Manager."); }
	
	void RenderManager::initConfig(const bool cullface, const bool depthtest, const bool alphablending)
	{
		m_renderer_api->initConfig(cullface, depthtest, alphablending);
	}
	void RenderManager::setViewPort(const uint32_t x, const uint32_t y, const uint32_t width, uint32_t height)
	{
		m_renderer_api->setViewPort(x, y, width, height);
	}
	void RenderManager::setClearColor(const glm::vec4& color) const
	{
		m_renderer_api->setClearColor(color);
	}
	void RenderManager::clear()					{ m_renderer_api->clear();}
	void RenderManager::clearColor()			{ m_renderer_api->clearColor();}
	void RenderManager::clearDepth()			{ m_renderer_api->clearColor();}	
	void RenderManager::enableCullFace()		{ m_renderer_api->enableCullFace();}
	void RenderManager::disableCullFace()		{ m_renderer_api->disableCullFace();}
	void RenderManager::enableDepthTest()		{ m_renderer_api->enableDepthTest();}
	void RenderManager::disableDepthTest()		{ m_renderer_api->disableDepthTest();}
	void RenderManager::enableAlphaBlending()	{ m_renderer_api->enableAlphaBlending();}
	void RenderManager::disableAlphaBlending()	{ m_renderer_api->disableAlphaBlending();}

	void RenderManager::linePolygonMode(const bool type) const
	{
		m_renderer_api->linePolygonMode(type);
	}
	void RenderManager::Draw(const VAO* vao) const
	{
		m_renderer_api->Draw(vao);
	}
}

