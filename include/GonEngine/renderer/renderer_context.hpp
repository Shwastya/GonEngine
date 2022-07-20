#pragma once

namespace gon {

	class RendererContext
	{
	public:

		RendererContext() = default;
		virtual ~RendererContext() = default;

		RendererContext(const RendererContext&) = delete;
		RendererContext& operator=(const RendererContext&) = delete;

		RendererContext(RendererContext&&) noexcept = delete;
		RendererContext& operator=(RendererContext&&) noexcept = delete;


		virtual void init() = 0;
		virtual void swapBuffers() = 0;
	};


}