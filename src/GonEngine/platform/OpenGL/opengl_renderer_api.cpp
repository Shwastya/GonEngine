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
		if (depthtest) OpenGLRendererAPI::enableDepthTest();
		else OpenGLRendererAPI::disableDepthTest();

		// Se habilita el Alpha Blending (alpha|depth channel textures)
		if (alphablending) OpenGLRendererAPI::enableAlphaBlending();
		else OpenGLRendererAPI::disableAlphaBlending();
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
		glCullFace(GL_BACK);
	}
	void OpenGLRendererAPI::disableCullFace()
	{
		glDisable(GL_CULL_FACE);	
		glCullFace(GL_BACK);
	}
	void OpenGLRendererAPI::enableDepthTest()
	{
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS); // (el mas habitual) el que tiene la prof. mas pequenya es el que queda
	}
	void OpenGLRendererAPI::disableDepthTest()
	{
		glDisable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS); // (el mas habitual) el que tiene la prof. mas pequenya es el que queda
	}
	void OpenGLRendererAPI::enableAlphaBlending()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	void OpenGLRendererAPI::disableAlphaBlending()
	{
		glDisable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	void OpenGLRendererAPI::linePolygonMode(const bool type) const
	{
		glPolygonMode(GL_FRONT_AND_BACK, type ? GL_LINE : GL_FILL);
	}
	
	// Draw final call
	// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*	
	void OpenGLRendererAPI::Draw(const VAO* vao) const
	{
		glDrawElements(GL_TRIANGLES, vao->getEBO()->nIndices(), GL_UNSIGNED_INT, nullptr);
	}
}