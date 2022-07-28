#pragma once
#include "GonEngine/renderer/renderer_api.hpp"

namespace Gon {

	class OpenGLRendererAPI final : public RendererAPI 
	{
	public:
		OpenGLRendererAPI() = default;

		virtual void initConfig(const bool cullface, const bool depthtest, const bool alphablending) override;

		virtual void setClearColor(const glm::vec4& color) const override;
		// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*	
		virtual void clear()		override;	// color & depth
		virtual void clearColor()	override;	// color only
		virtual void clearDepth()	override;	// depth only
		// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*	
		
		// separate methods
		// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
		virtual void enableCullFace()		override;
		virtual void disableCullFace()		override;

		virtual void enableDepthTest()		override;
		virtual void disableDepthTest()		override;

		virtual void enableAlphaBlending()	override;
		virtual void disableAlphaBlending() override;
		// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

		virtual void linePolygonMode(const bool type) const override;

		// Draw final call
		// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*	
		virtual void Draw(const VAO* vao) const override;
	};
}