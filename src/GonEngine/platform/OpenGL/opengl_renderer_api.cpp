#include "GonEngine/log.hpp"
#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/renderer/renderer_api.hpp"
#include "GonEngine/platform/OpenGL/opengl_vao.hpp"
#include "GonEngine/platform/OpenGL/opengl_renderer_api.hpp"
#include <glad/glad.h>

namespace Gon {	

	void OpenGLRendererAPI::initConfig(const bool cullface, const bool depthtest, const bool alphablending)
	{
		// por defecto caras traseras no se pintaran
		if (cullface) OpenGLRendererAPI::enableCullFace();
		else OpenGLRendererAPI::disableDepthTest();

		// Se habilita el test de profundidad para las geometrias 3D
		if (depthtest) 
		{
			OpenGLRendererAPI::enableDepthTest();
			OpenGLRendererAPI::setLessDepthTest();
		}
		
		else OpenGLRendererAPI::disableDepthTest();

		// Se habilita el Alpha Blending (alpha|depth channel textures)
		if (alphablending) OpenGLRendererAPI::enableAlphaBlending();
		else OpenGLRendererAPI::disableAlphaBlending();
	}

	void OpenGLRendererAPI::setViewPort(const uint32_t x, const uint32_t y, const uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
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

	// separate methods
	// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	void OpenGLRendererAPI::enableCullFace() 
	{
		glEnable(GL_CULL_FACE);		
	}
	void OpenGLRendererAPI::disableCullFace()
	{
		glDisable(GL_CULL_FACE);	
	}
	void OpenGLRendererAPI::enableDepthTest()
	{
		glEnable(GL_DEPTH_TEST);		
	}
	void OpenGLRendererAPI::disableDepthTest()
	{
		glDisable(GL_DEPTH_TEST);
	}
	void OpenGLRendererAPI::setFalseDepthMask()
	{
		glDepthMask(GL_FALSE);
	}
	void OpenGLRendererAPI::setTrueDepthMask()
	{
		glDepthMask(GL_TRUE);
	}
	void OpenGLRendererAPI::setEqualDepthTest()
	{		
		glDepthFunc(GL_LEQUAL);
	}
	void OpenGLRendererAPI::setLessDepthTest()
	{
		glDepthFunc(GL_LESS);
	}
	void OpenGLRendererAPI::enableAlphaBlending()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	void OpenGLRendererAPI::disableAlphaBlending()
	{
		glDisable(GL_BLEND);
	}
	// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	void OpenGLRendererAPI::linePolygonMode(const bool type) const
	{
		glPolygonMode(GL_FRONT_AND_BACK, type ? GL_LINE : GL_FILL);
	}
	
	// Draw final call
	// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*	
	void OpenGLRendererAPI::DrawElements(const VAO* vao) const
	{
		glDrawElements(GL_TRIANGLES, vao->getEBO()->nIndices(), GL_UNSIGNED_INT, nullptr);
	}
	void OpenGLRendererAPI::DrawElements(const uint32_t count) const
	{
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}
	void OpenGLRendererAPI::DrawArrays(const uint32_t count) const
	{
		glDrawArrays(GL_TRIANGLES, 0, count);
		
	}
}