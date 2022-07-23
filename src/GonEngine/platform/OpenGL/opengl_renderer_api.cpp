#include "GonEngine/log.hpp"
#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/renderer/renderer_api.hpp"
#include "GonEngine/platform/OpenGL/opengl_vao.hpp"
#include "GonEngine/platform/OpenGL/opengl_renderer_api.hpp"
#include <glad/glad.h>

namespace gon {

	

	void OpenGLRendererAPI::initDefaultConfiguration()
	{
		// por defecto caras traseras no se pintaran
		OpenGLRendererAPI::enableCullFace();
	}

	void OpenGLRendererAPI::setClearColor(const glm::vec4& color) const
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	void OpenGLRendererAPI::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void OpenGLRendererAPI::clearColor() { glClear(GL_COLOR_BUFFER_BIT); }
	void OpenGLRendererAPI::clearDepth() { glClear(GL_DEPTH_BUFFER_BIT); }
	// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

	void OpenGLRendererAPI::Draw(const VAO* vao) const
	{
		glDrawElements(GL_TRIANGLES, vao->getEBO()->nIndices(), GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRendererAPI::enableCullFace() 
	{
		glEnable(GL_CULL_FACE);		glCullFace(GL_BACK);
	}
	void OpenGLRendererAPI::disableCullFace()
	{
		glDisable(GL_CULL_FACE);	glCullFace(GL_BACK);
	}

	void OpenGLRendererAPI::linePolygonMode(const bool type) const
	{
		glPolygonMode(GL_FRONT_AND_BACK, type ? GL_LINE : GL_FILL);
	}

	

	
}