#include "GonEngine/platform/OpenGL/opengl_texture_cube_map.hpp"
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
			GON_ASSERT(false, "Not API selected for Texture");
			return nullptr;
		case API::OpenGL:
			return make_u_ptr<OpenGLTexture2D>(path, format);
		case API::DirectX:
			GON_WARN("DirectX not implemented. OpenGL Texture by default");
			return make_u_ptr<OpenGLTexture2D>(path, format);
		case API::Vulkan:
			GON_WARN("Vulkan not implemented. OpenGL Texture by default");
			return make_u_ptr<OpenGLTexture2D>(path, format);
		default:
			GON_ASSERT(false, "Unknown API for texture");
			return nullptr;
		}
	}

	u_ptr<Texture2D> Texture2D::create(uint32_t width, uint32_t height)
	{
		width, height;
		return u_ptr<Texture2D>();
	}



	u_ptr<CubeMapText> CubeMapText::create(const std::vector<std::string>& path, CubeMapText::Format format)
	{
		switch (APIContext::getAPI())
		{
		case API::None:
			GON_ASSERT(false, "Not API selected for Texture");
			return nullptr;
		case API::OpenGL:
			return make_u_ptr<OpenGLCubeMapText>(path, format);
		case API::DirectX:
			GON_WARN("DirectX not implemented. OpenGL Texture by default");
			return make_u_ptr<OpenGLCubeMapText>(path, format);
		case API::Vulkan:
			GON_WARN("Vulkan not implemented. OpenGL Texture by default");
			return make_u_ptr<OpenGLCubeMapText>(path, format);
		default:
			GON_ASSERT(false, "Unknown API for texture");
			return nullptr;
		}
	}

}