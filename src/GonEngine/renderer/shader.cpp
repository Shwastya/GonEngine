#include "GonEngine/platform/OpenGL/opengl_shader.hpp"
#include "GonEngine/renderer/renderer_api.hpp"
#include "GonEngine/renderer/shader.hpp"
#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/window.hpp"
#include "GonEngine/log.hpp"
#include <sstream>

namespace gon
{
	s_ptr<Shader>Shader::Create(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath)
	{
		switch (RendererApi::_API())
		{
		case API::None:
			// is needed some code?
			GON_WARN("not API selected for shader.");
			return nullptr; break;

		case API::OpenGL:

			return std::make_shared<OpenGLShader>(vertexPath, fragmentPath, geometryPath); break;

		case API::DirectX:

			GON_WARN("DirectX not implemented. OpenGL shader by default");
			return std::make_shared<OpenGLShader>(vertexPath, fragmentPath, geometryPath); break;


		case API::Vulkan:
			GON_WARN("Vulkan not implemented. OpenGL shader by default");
			return std::make_shared<OpenGLShader>(vertexPath, fragmentPath, geometryPath); break;

		default:
			GON_WARN("Unknown shader API.");
			return nullptr; break;
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