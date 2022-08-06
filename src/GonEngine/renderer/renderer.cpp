#include "GonEngine/renderer/management/render_manager.hpp"
#include "GonEngine/renderer/renderer.hpp"
#include "GonEngine/renderer/renderer3D.hpp"


namespace Gon {

	u_ptr<Renderer::MatrixData> Renderer::s_matrixData{ nullptr };

	void Renderer::init(const bool cullface, const bool depthtest, const bool alphablending)
	{
		RenderCall::init(cullface, depthtest, alphablending);
		s_matrixData = make_u_ptr<MatrixData>();
		Renderer3D::init();
	}
	void Renderer::reset()
	{		
		Renderer3D::reset();
		s_matrixData.reset();
		RenderCall::reset();		
	}
	void Renderer::setViewPorts(const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height)
	{
		RenderCall::setViewPort(x, y, width, height);
	}
	void Renderer::onWindowResize(const uint32_t width, const uint32_t height)
	{
		RenderCall::setViewPort(0, 0, width, height);
	}

}