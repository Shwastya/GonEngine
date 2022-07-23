#pragma once
#include "GonEngine/renderer/renderer_api.hpp"


namespace gon {

	class OpenGLRendererAPI final : public RendererAPI 
	{
	public:
		OpenGLRendererAPI() = default;

		virtual void initDefaultConfiguration() override;

		virtual void setClearColor(const glm::vec4& color) const override;
		// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*	
		virtual void clear() override;
		virtual void clearColor() override;
		virtual void clearDepth() override;
		// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*	

		virtual void Draw(const VAO* vao) const override;

		virtual void enableCullFace() override;
		virtual void disableCullFace() override;

		virtual void linePolygonMode(const bool type) const override;
	};
}