#include "GonEngine/renderer/management/render_manager.hpp"
#include "GonEngine/renderer/renderer.hpp"

namespace Gon {

	void Renderer::init(const bool cullface, const bool depthtest, const bool alphablending)
	{
		RenderCall::init(cullface, depthtest, alphablending);
	}
	void Renderer::reset()
	{
		RenderCall::reset();
	}
	void Renderer::setViewPorts(const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height)
	{
		RenderCall::setViewPort(x, y, width, height);
	}	
}