#pragma once
#include "GonEngine/platform/OpenGL/opengl_context.hpp"
#include "GonEngine/log.hpp"
#include "GonEngine/memcfg/goncfg.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Gon {

	OpenGLContext::OpenGLContext(GLFWwindow* GLFWwin)
		: m_GLFWwindow(GLFWwin)
	{}

	void OpenGLContext::init()
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); 
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

		glfwMakeContextCurrent(m_GLFWwindow);
		int result = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		GON_ASSERT("Error initializing GLAD! {0}:", result);
	}
	void OpenGLContext::swapBuffers()
	{
		glfwSwapBuffers(m_GLFWwindow);		
	}
	void OpenGLContext::onWindowResize(const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height)
	{
		
		glViewport(0, 0, width, height);
	}
}