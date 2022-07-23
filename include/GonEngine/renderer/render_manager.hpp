#pragma once
//#include "GonEngine/renderer/renderer_api.hpp"
#include "GonEngine/memcfg/scp_ptr.hpp"

namespace gon {	

	class RendererAPI; struct VAO;

	class RenderManager
	{
	public:
		RenderManager();
		~RenderManager();

		void initDefaultConfiguration();

		void setClearColor(const glm::vec4& color) const;

		void clear();
		void clearColor();
		void clearDepth(); 

		void Draw(const VAO* vao) const;

		void enableCullFace();
		void disableCullFace();

		void linePolygonMode(const bool type) const;

	private:
		u_ptr<RendererAPI> m_renderer_api;
	};
}