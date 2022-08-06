#pragma once
#include "GonEngine/renderer/api_context.hpp"

struct GLFWwindow;

namespace Gon {

	class OpenGLContext final : public APIContext
	{
	public:


		OpenGLContext(GLFWwindow* _GLFWwindow);	
		virtual ~OpenGLContext() = default;

		OpenGLContext(const OpenGLContext&) = default;
		OpenGLContext& operator=(const OpenGLContext&) = default;

		OpenGLContext(OpenGLContext&&) noexcept = default;
		OpenGLContext& operator=(OpenGLContext&&) noexcept = default;

		virtual void init() override;
		virtual void swapBuffers() override;

	private:
		GLFWwindow* m_GLFWwindow;
	};
}