#include "GonEngine/platform/OpenGL/opengl_vbo.hpp"
#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/log.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace gon {

	OpenglVBO::OpenglVBO(float* vertices, const uint32_t size)
		:m_id_vbo(NULL)
	{
		glGenBuffers(1, &m_id_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_id_vbo);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
		GON_TRACE("[CREATED] An OpenGL VBO (Vertex Buffer Object). ");
	}

	OpenglVBO::~OpenglVBO()
	{
		glDeleteBuffers(1, &m_id_vbo);
		GON_TRACE("[DESTROYED] VBO from the GPU and memory.");
	}

	void OpenglVBO::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_id_vbo);
	}

	void OpenglVBO::unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	OpenglEBO::OpenglEBO(const uint32_t* indices, const uint32_t nIndices)
		: m_id_ebo(0), m_nIndices(nIndices)
	{
		glGenBuffers(1, &m_id_ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * nIndices, indices, GL_STATIC_DRAW);
		GON_TRACE("[CREATED] An OpenGL GPU EBO (Element Buffer Object).");
	}

	OpenglEBO::~OpenglEBO()
	{
		glDeleteBuffers(1, &m_id_ebo);
		GON_TRACE("[DESTROYED] EBO from the GPU and memory.");
	}

	void OpenglEBO::bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id_ebo);
	}

	void OpenglEBO::unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	const uint32_t OpenglEBO::nIndices()
	{
		return m_nIndices;
	}

}