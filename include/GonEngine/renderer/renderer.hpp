#pragma once
#include "GonEngine/memcfg/scp_ptr.hpp"
#include <glm/glm.hpp>


namespace Gon {

	#define _model	 Renderer::s_matrixData->Model
	#define _view	 Renderer::s_matrixData->View
	#define _proj	 Renderer::s_matrixData->Projection

	class Renderer
	{
	public:

		Renderer()	= delete;
		~Renderer() = delete;	

		static void init(const bool cullface, const bool depthtest, const bool alphablending);
		static void reset();

		static void setViewPorts(const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height);
		static void onWindowResize(const uint32_t width, const uint32_t height);

		struct MatrixData
		{
			glm::mat4 Model		 { 1.0f };
			glm::mat4 View		 { 1.0f };
			glm::mat4 Projection { 1.0f };
		};

		static u_ptr<MatrixData> s_matrixData;
	};
}