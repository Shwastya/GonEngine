#pragma once
#include "GonEngine/renderer/renderer_api.hpp"


namespace gon {

	class OpenGLRendererAPI final : public RendererApi 
	{
		OpenGLRendererAPI() = default;

		virtual void init() override;
		virtual void clearColor(const float r, const float g, const float b, const float a) override;

		virtual void clearBuffer() override;
		virtual void clearColorBuffer() override;
		virtual void clearDepthBuffer() override;

	};
}