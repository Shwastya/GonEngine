#pragma once
#include "GonEngine/memcfg/scp_ptr.hpp"
#include <glm/glm.hpp>

namespace Gon {

	// Forward declarations
	// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	struct VAO;
	class Camera;
	class Shader;
	class CameraMan;
	// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

	class SceneRenderer
	{
	public:

		SceneRenderer();
		~SceneRenderer();	

		// static functions
		// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
		void setViewPorts(const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height);

		void shareCam(const s_ptr<CameraMan>& cam);
		void InitConfiguration(const bool cullface, const bool depthtest, const bool alphablending);

	

		void begin(const glm::mat4& view, const glm::mat4 projection);
		void begin();
		void end();

		void submit(const VAO* vao, const Shader* shader, const glm::mat4& model = glm::mat4{ 0.1f });

	protected:

		
		struct MatrixData
		{
			glm::mat4 View;  
			glm::mat4 Projection;
		};

		s_ptr<CameraMan> m_cameraMan;
		u_ptr<MatrixData> m_data;

		u_ptr<RenderManager> m_render;
		
		
	};
}