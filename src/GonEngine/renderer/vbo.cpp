#include "GonEngine/platform/OpenGL/opengl_vbo.hpp"
#include "GonEngine/renderer/api_context.hpp"
#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/log.hpp"

namespace gon {

	u_ptr<VBO> VBO::create(const float* vertices, const uint32_t size)
	{
		switch (APIContext::getAPI())
		{
		case API::None:
			GON_ASSERT(false, "Not API selected for VBO.");
			return nullptr;
		case API::OpenGL:
			return std::make_unique<OpenglVBO>(vertices, size);
		case API::DirectX:
			GON_WARN("DirectX not implemented. OpenGL VBO by default");
			return std::make_unique<OpenglVBO>(vertices, size);
		case API::Vulkan:
			GON_WARN("Vulkan not implemented. OpenGL VBO by default");
			return std::make_unique<OpenglVBO>(vertices, size);
		default:
			GON_ASSERT(false, "Unknown shader API.");
			return nullptr;
		}		
	}
	u_ptr<EBO> EBO::create(const uint32_t* indices, const uint32_t size)
	{
		switch (APIContext::getAPI())
		{
		case API::None:
			GON_ASSERT(false, "Not API selected for shader.");
			return nullptr;
		case API::OpenGL:
			return std::make_unique<OpenglEBO>(indices, size);
		case API::DirectX:
			GON_WARN("DirectX not implemented. OpenGL VBO by default");
			return std::make_unique<OpenglEBO>(indices, size);
		case API::Vulkan:
			GON_WARN("Vulkan not implemented. OpenGL VBO by default");
			return std::make_unique<OpenglEBO>(indices, size);
		default:
			GON_ASSERT(false, "Unknown shader API.");
			return nullptr;
		}		
	}
}