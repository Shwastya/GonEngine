#pragma once
#include "GonEngine/renderer/api_context.hpp"

struct GLFWwindow;

namespace Gon {

	class OpenGLContext final : public APIContext
	{
	public:

		OpenGLContext(GLFWwindow* _GLFWwindow);	

		OpenGLContext(const OpenGLContext&) = default;
		OpenGLContext& operator=(const OpenGLContext&) = default;

		OpenGLContext(OpenGLContext&&) noexcept = default;
		OpenGLContext& operator=(OpenGLContext&&) noexcept = default;

		virtual void init() override;
		virtual void swapBuffers() override;

		virtual void onWindowResize(const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height) override;

	private:
		GLFWwindow* m_GLFWwindow;
	};
}