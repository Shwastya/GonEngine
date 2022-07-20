#pragma once
#include "GonEngine/renderer/renderer_context.hpp"

struct GLFWwindow;

namespace gon
{

	class OpenGLContext final : public RendererContext
	{
	public:

		OpenGLContext(GLFWwindow* _GLFWwindow);		

		virtual void init() override;
		virtual void swapBuffers() override;

	private:
		GLFWwindow* m_GLFWwindow;
	};
}