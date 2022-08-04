#include "GonEngine/platform/OpenGL/opengl_vao.hpp"
#include "GonEngine/renderer/api_context.hpp"

namespace Gon {
	
	u_ptr<VAO> VAO::create(const size_t reserve = 5)
	{
		switch (APIContext::getAPI())
		{
		case API::None:
			GON_ASSERT(false, "Not API selected for VAO.");
			return nullptr;
		case API::OpenGL:
			return std::make_unique<OpenglVAO>(reserve);
		case API::DirectX:
			GON_WARN("DirectX not implemented. OpenGL VBO by default");
			return std::make_unique<OpenglVAO>(reserve);
		case API::Vulkan:
			GON_WARN("Vulkan not implemented. OpenGL VBO by default");
			return std::make_unique<OpenglVAO>(reserve);
		default:
			GON_ASSERT(false, "Unknown shader API.");
			return nullptr;
		}
	}
}