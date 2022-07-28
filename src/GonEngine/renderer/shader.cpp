#include "GonEngine/platform/OpenGL/opengl_shader.hpp"
#include "GonEngine/renderer/api_context.hpp"
#include "GonEngine/renderer/shader.hpp"
#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/window.hpp"
#include "GonEngine/log.hpp"
#include <sstream>

namespace Gon
{
	u_ptr<Shader>Shader::create(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath)
	{
		switch (APIContext::getAPI())
		{
		case API::None:
			// is needed some code?
			GON_WARN("not API selected for shader.");
			return nullptr;

		case API::OpenGL:

			return std::make_unique<OpenGLShader>(vertexPath, fragmentPath, geometryPath);

		case API::DirectX:

			GON_WARN("DirectX not implemented. OpenGL shader by default");
			return std::make_unique<OpenGLShader>(vertexPath, fragmentPath, geometryPath);


		case API::Vulkan:
			GON_WARN("Vulkan not implemented. OpenGL shader by default");
			return std::make_unique<OpenGLShader>(vertexPath, fragmentPath, geometryPath);

		default:
			GON_WARN("Unknown shader API.");
			return nullptr;
		}
	}

	//s_ptr<Shader>Shader::Create(const std::string& GLSLFilePath)
	//{
	//	switch (RendererApi::_API())
	//	{
	//	case API::None:
	//		// is needed some code?
	//		GON_WARN("not API selected for shader.");
	//		return nullptr; break;

	//	case API::OpenGL:

	//		return std::make_shared<OpenGLShader>(GLSLFilePath); break;

	//	case API::DirectX:

	//		GON_WARN("DirectX not implemented. OpenGL shader by default");
	//		return std::make_shared<OpenGLShader>(GLSLFilePath); break;

	//	case API::Vulkan:
	//		
	//		GON_WARN("Vulkan not implemented. OpenGL shader by default");
	//		return std::make_shared<OpenGLShader>(GLSLFilePath); break;

	//	default:
	//		GON_WARN("Unknown shader API.");
	//		return nullptr; break;
	//	}
	//}
}