#pragma once
#include <glm/glm.hpp>
#include "GonEngine/memcfg/scp_ptr.hpp"

namespace Gon {	

	// Forward declarations
	// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	class RendererAPI;
	struct VAO;
	// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

	class RenderCall
	{
	public:
		RenderCall()	= delete;
		~RenderCall()	= delete;

		static void init(const bool cullface, const bool depthtest, const bool alphablending);
		static void reset();

		static void setViewPort(const uint32_t x, const uint32_t y, const uint32_t width, uint32_t height);

		static void setClearColor(const glm::vec4& color);

		// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*	
		static void clear();
		static void clearColor();
		static void clearDepth();
		// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*	
		
		// separate methods
		// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
		static void enableCullFace();
		static void disableCullFace();

		static void enableDepthTest();
		static void disableDepthTest();

		static void enableAlphaBlending();
		static void disableAlphaBlending();
		// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

		static void linePolygonMode(const bool type);

		// Draw final call
		// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*	
		static void Draw(const VAO* vao);

	private:
		static u_ptr<RendererAPI> s_renderer_api;
	};
}