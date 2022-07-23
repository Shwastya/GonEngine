#pragma once

#include <glm/glm.hpp>

namespace gon {
	
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

		virtual void initDefaultConfiguration() = 0;

		virtual void setClearColor(const glm::vec4& color) const = 0;
		// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*	
		virtual void clear() = 0;
		virtual void clearColor() = 0;
		virtual void clearDepth() = 0;
		// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

		virtual void Draw(const VAO* vao) const = 0;

		virtual void enableCullFace()  = 0;
		virtual void disableCullFace() = 0;

		virtual void linePolygonMode(const bool type) const = 0;


		

		
			
	};
}