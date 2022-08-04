#pragma once
#include "GonEngine/memcfg/scp_ptr.hpp"
#include <glm/glm.hpp>

#define Vec3	const glm::vec3&
#define Vec4	const glm::vec4&
#define Texture	const Texture2D*

#define _current s_utils->SType
#define _shader	 s_utils->Shader

#define _model	 s_utils->Model
#define _view	 s_utils->View
#define _proj	 s_utils->Projection

namespace Gon {

	class Renderer
	{
	public:

		Renderer()	= delete;
		~Renderer() = delete;	

		static void init(const bool cullface, const bool depthtest, const bool alphablending);
		static void reset();

		static void setViewPorts(const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height);
	};
}