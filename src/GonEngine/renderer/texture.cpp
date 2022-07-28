#include "GonEngine/platform/OpenGL/opengl_texture.hpp"
#include "GonEngine/renderer/api_context.hpp"
#include "GonEngine/renderer/texture.hpp"
#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/log.hpp"


namespace Gon {


	u_ptr<Texture2D> Texture2D::create(const std::string& path, Texture2D::Format format)
	{
		switch (APIContext::getAPI())
		{
		case API::None:
			GON_ASSERT(false, "Not API selected for Texture.");
			return nullptr;
		case API::OpenGL:
			return std::make_unique<OpenGLTexture2D>(path, format);
		case API::DirectX:
			GON_WARN("DirectX not implemented. OpenGL Texture by default");
			return std::make_unique<OpenGLTexture2D>(path, format);
		case API::Vulkan:
			GON_WARN("Vulkan not implemented. OpenGL Texture by default");
			return std::make_unique<OpenGLTexture2D>(path, format);
		default:
			GON_ASSERT(false, "Unknown shader API.");
			return nullptr;
		}
		return nullptr; // borrar
	}

	u_ptr<Texture2D> Texture2D::create(uint32_t width, uint32_t height)
	{
		return u_ptr<Texture2D>();
	}

}