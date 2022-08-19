#pragma once

#include <glm/glm.hpp>

namespace Gon {
	
	struct VAO;
	class RendererAPI
	{
	public:		

		RendererAPI() = default;
		virtual ~RendererAPI() = default;

		RendererAPI(const RendererAPI&) = delete;
		RendererAPI& operator=(const RendererAPI&) = delete;

		RendererAPI(RendererAPI&&) noexcept = delete;
		RendererAPI& operator=(RendererAPI&&) noexcept = delete;

		virtual void initConfig(const bool cullface = true, const bool depthtest = true, const bool alphablending = true) = 0;
		virtual void setViewPort(const uint32_t x, const uint32_t y, const uint32_t width, uint32_t height) = 0;

		virtual void setClearColor(const glm::vec4& color) const = 0;
		// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*	
		virtual void clear()		= 0;	// color & depth
		virtual void clearColor()	= 0;	// color only
		virtual void clearDepth()	= 0;	// depth only
		// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

		// separate methods
		// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
		virtual void enableCullFace()		 = 0;
		virtual void disableCullFace()		 = 0;

		virtual void enableDepthTest()		 = 0;
		virtual void disableDepthTest()		 = 0;

		virtual void setFalseDepthMask()	 = 0;
		virtual void setTrueDepthMask()		 = 0;

		virtual void setEqualDepthTest()	 = 0;
		virtual void setLessDepthTest()		 = 0;

		virtual void enableAlphaBlending()	 = 0;
		virtual void disableAlphaBlending()  = 0;
		// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

		virtual void linePolygonMode(const bool type) const = 0;

		// Draw final call
		// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
		virtual void DrawElements(const VAO* vao) const = 0;
		virtual void DrawElements(const uint32_t count) const = 0;
		virtual void DrawArrays(const uint32_t count) const = 0;



	};
}