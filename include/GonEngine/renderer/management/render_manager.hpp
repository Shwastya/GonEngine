#pragma once
#include <glm/glm.hpp>
#include "GonEngine/memcfg/scp_ptr.hpp"

namespace Gon {	

	class RendererAPI; struct VAO;

	class RenderManager
	{
	public:
		RenderManager();
		~RenderManager();

		void initConfig(const bool cullface, const bool depthtest, const bool alphablending);
		void setViewPort(const uint32_t x, const uint32_t y, const uint32_t width, uint32_t height);

		void setClearColor(const glm::vec4& color) const;

		// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*	
		void clear();
		void clearColor();
		void clearDepth(); 
		// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*	
		
		// separate methods
		// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
		void enableCullFace();
		void disableCullFace();

		void enableDepthTest();
		void disableDepthTest();

		void enableAlphaBlending();
		void disableAlphaBlending();
		// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

		void linePolygonMode(const bool type) const;

		// Draw final call
		// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*	
		void Draw(const VAO* vao) const;

	private:
		u_ptr<RendererAPI> m_renderer_api;
	};
}