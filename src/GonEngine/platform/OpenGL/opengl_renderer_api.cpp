#include "GonEngine/log.hpp"
#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/renderer/renderer_api.hpp"
#include "GonEngine/platform/OpenGL/opengl_renderer_api.hpp"
#include <glad/glad.h>

namespace gon {

	void OpenGLRendererAPI::init()
	{
		GON_WARN("'OpenGlRendererAPI' empty function");
	}

	void OpenGLRendererAPI::clearColor(const float r, const float g, const float b, const float a)
	{
		glClearColor(r, g, b, a);
	}

	void OpenGLRendererAPI::clearBuffer()
	{
		GON_WARN("'clearBuffer()' empty function");
	}

	void OpenGLRendererAPI::clearColorBuffer()
	{
		GON_WARN("'clearColorBuffer() empty function");
	}

	void OpenGLRendererAPI::clearDepthBuffer()
	{
		GON_WARN("'clearDepthBuffer() empty function");
	}	
}