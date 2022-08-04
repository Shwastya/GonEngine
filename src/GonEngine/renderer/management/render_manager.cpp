#include "GonEngine/platform/OpenGL/opengl_renderer_api.hpp"
#include "GonEngine/renderer/management/render_manager.hpp"
#include "GonEngine/renderer/api_context.hpp"
#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/log.hpp"

namespace Gon {
	
	
	u_ptr<RendererAPI> RenderCall::s_renderer_api{ nullptr };

	void RenderCall::init(const bool cullface, const bool depthtest, const bool alphablending)
	{
		GON_TRACE("[STATIC INITIALIZATION] Renderer API.");

		switch (APIContext::getAPI())
		{
		case API::None:
			GON_ASSERT(false, "Not renderer API selected.");
			break;
		case API::OpenGL:
			s_renderer_api = std::make_unique<OpenGLRendererAPI>();
			break;
		case API::DirectX:
			GON_WARN("DirectX not implemented. OpenGL renderer by default");
			s_renderer_api = std::make_unique<OpenGLRendererAPI>();
			break;
		case API::Vulkan:
			GON_WARN("Vulkan not implemented. OpenGL renderer by default");
			s_renderer_api = std::make_unique<OpenGLRendererAPI>();
			break;
		default:
			GON_ASSERT(false, "Unknown renderer API.");
			break;
		}
		s_renderer_api->initConfig(cullface, depthtest, alphablending);
	}
	void RenderCall::reset()	
	{ 
		s_renderer_api.reset();
		s_renderer_api = nullptr;
	}
	void RenderCall::setViewPort(const uint32_t x, const uint32_t y, const uint32_t width, uint32_t height)
	{
		s_renderer_api->setViewPort(x, y, width, height);
	}
	void RenderCall::setClearColor(const glm::vec4& color)
	{
		s_renderer_api->setClearColor(color);
	}
	void RenderCall::clear()				{ s_renderer_api->clear();}
	void RenderCall::clearColor()			{ s_renderer_api->clearColor();}
	void RenderCall::clearDepth()			{ s_renderer_api->clearColor();}	
	void RenderCall::enableCullFace()		{ s_renderer_api->enableCullFace();}
	void RenderCall::disableCullFace()		{ s_renderer_api->disableCullFace();}
	void RenderCall::enableDepthTest()		{ s_renderer_api->enableDepthTest();}
	void RenderCall::disableDepthTest()		{ s_renderer_api->disableDepthTest();}
	void RenderCall::enableAlphaBlending()	{ s_renderer_api->enableAlphaBlending();}
	void RenderCall::disableAlphaBlending()	{ s_renderer_api->disableAlphaBlending();}

	void RenderCall::linePolygonMode(const bool type)
	{
		s_renderer_api->linePolygonMode(type);
	}
	void RenderCall::Draw(const VAO* vao)
	{
		s_renderer_api->Draw(vao);
	}
}

