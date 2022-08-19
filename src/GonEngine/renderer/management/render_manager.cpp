#include "GonEngine/platform/OpenGL/opengl_renderer_api.hpp"
#include "GonEngine/renderer/management/render_manager.hpp"
#include "GonEngine/renderer/api_context.hpp"
#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/log.hpp"

namespace Gon {
	
	
	u_ptr<RendererAPI> RenderMan::s_renderer_api{ nullptr };

	void RenderMan::init(const bool cullface, const bool depthtest, const bool alphablending)
	{
		GON_TRACE("[STATIC INITIALIZATION] Renderer API.");

		switch (APIContext::getAPI())
		{
		case API::None:
			GON_ASSERT(false, "Not renderer API selected.");
			break;
		case API::OpenGL:
			s_renderer_api = make_u_ptr<OpenGLRendererAPI>();
			break;
		case API::DirectX:
			GON_WARN("DirectX not implemented. OpenGL renderer by default");
			s_renderer_api = make_u_ptr<OpenGLRendererAPI>();
			break;
		case API::Vulkan:
			GON_WARN("Vulkan not implemented. OpenGL renderer by default");
			s_renderer_api = make_u_ptr<OpenGLRendererAPI>();
			break;
		default:
			GON_ASSERT(false, "Unknown renderer API.");
			break;
		}
		s_renderer_api->initConfig(cullface, depthtest, alphablending);
	}
	void RenderMan::reset()	
	{ 
		s_renderer_api.reset();
		s_renderer_api = nullptr;
	}
	void RenderMan::setViewPort(const uint32_t x, const uint32_t y, const uint32_t width, uint32_t height)
	{
		s_renderer_api->setViewPort(x, y, width, height);
	}
	void RenderMan::setClearColor(const glm::vec4& color)
	{
		s_renderer_api->setClearColor(color);
	}
	void RenderMan::clear()					{ s_renderer_api->clear();}
	void RenderMan::clearColor()			{ s_renderer_api->clearColor();}
	void RenderMan::clearDepth()			{ s_renderer_api->clearColor();}	
	void RenderMan::enableCullFace()		{ s_renderer_api->enableCullFace();}
	void RenderMan::disableCullFace()		{ s_renderer_api->disableCullFace();}
	void RenderMan::enableDepthTest()		{ s_renderer_api->enableDepthTest();}
	void RenderMan::disableDepthTest()		{ s_renderer_api->disableDepthTest();}
	void RenderMan::setFalseDepthMask()		{ s_renderer_api->setFalseDepthMask();}
	void RenderMan::setTrueDepthMask()		{ s_renderer_api->setTrueDepthMask();}
	void RenderMan::setEqualDepthTest()		{ s_renderer_api->setEqualDepthTest();}
	void RenderMan::setLessDepthTest()		{ s_renderer_api->setLessDepthTest();}
	void RenderMan::enableAlphaBlending()	{ s_renderer_api->enableAlphaBlending();}
	void RenderMan::disableAlphaBlending()	{ s_renderer_api->disableAlphaBlending();}

	void RenderMan::linePolygonMode(const bool type)
	{
		s_renderer_api->linePolygonMode(type);
	}
	void RenderMan::Draw(const VAO* vao)
	{
		s_renderer_api->DrawElements(vao);
	}
	void RenderMan::Draw(const uint32_t count)
	{
		s_renderer_api->DrawElements(count);
	}
	void RenderMan::DrawArrays(const uint32_t count)
	{
		s_renderer_api->DrawArrays(count);
	}
}

