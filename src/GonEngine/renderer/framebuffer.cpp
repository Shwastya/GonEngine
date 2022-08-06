#include "GonEngine/platform/OpenGL/opengl_framebuffer.hpp"
#include "GonEngine/renderer/api_context.hpp"
#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/log.hpp"

namespace Gon {

	u_ptr<FrameBuffer> FrameBuffer::create(const FBProps& specs)
	{
		switch (APIContext::getAPI())
		{
		case API::None:
			GON_ASSERT(false, "Not API selected for  FrameBuffers");
			return nullptr;
		case API::OpenGL:
			return make_u_ptr<OpenGLFrameBuffer>(specs);
		case API::DirectX:
			GON_WARN("DirectX not implemented. OpenGL FrameBuffers by default");
			return make_u_ptr<OpenGLFrameBuffer>(specs);
		case API::Vulkan:
			GON_WARN("Vulkan not implemented. OpenGL  FrameBuffers by default");
			return make_u_ptr<OpenGLFrameBuffer>(specs);
		default:
			GON_ASSERT(false, "Unknown shader API");
			return nullptr;
		}
	}
}