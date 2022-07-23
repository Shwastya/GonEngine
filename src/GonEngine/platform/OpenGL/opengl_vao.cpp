#include "GonEngine/platform/OpenGL/opengl_vao.hpp"
#include "GonEngine/platform/OpenGL/opengl_vbo.hpp"
#include <glad/glad.h>

namespace gon {

	static GLenum toOpenGLBaseType(DataType type)
	{
		switch (type)
		{
			case DataType::Float:	return GL_FLOAT;
			case DataType::Float2:	return GL_FLOAT;
			case DataType::Float3:	return GL_FLOAT;
			case DataType::Float4:	return GL_FLOAT;
			case DataType::Int:		return GL_INT;
			case DataType::Int2:	return GL_INT;
			case DataType::Int3:	return GL_INT;
			case DataType::Int4:	return GL_INT;
			case DataType::Mat3:	return GL_FLOAT;
			case DataType::Mat4:	return GL_FLOAT;
			case DataType::Bool:	return GL_BOOL;
		}
		return 0;
	}

	OpenglVAO::OpenglVAO(const size_t reserve = 5)  
	{
		glGenVertexArrays(1, &m_id_vao);
		reserve; //m_vbo_vec.reserve(reserve);
		GON_TRACE("[CREATED] An OpenGL VAO (Vertex Array Object). ");
	}

	OpenglVAO::~OpenglVAO()
	{
		glDeleteVertexArrays(1, &m_id_vao);
		GON_TRACE("[DESTROYED] VAO from the GPU and memory.");
	}

	void OpenglVAO::bind() const
	{
		glBindVertexArray(m_id_vao);
	}

	void OpenglVAO::unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenglVAO::takeVBO(u_ptr<VBO>& _vbo)
	{
		u_ptr<VBO> vbo = std::move(_vbo);

		glBindVertexArray(m_id_vao);
		vbo->bind();

		const size_t size = vbo->getLayout().getObjects().size();

		if (size < 1) GON_ERROR("Layout does not have any VBO (Vertex Buffer Object)");
	
		//else GON_WARN(" ... There are {0} components of the VBO in the VBO Layout ...", size);

		uint32_t idx = 0;

		auto layout = vbo->getLayout();

		for (const auto& object : layout)
		{
			glEnableVertexAttribArray(idx);
			glVertexAttribPointer
			(
				idx,
				object.compCount(),
				toOpenGLBaseType(object.m_type),
				object.m_normalized ? GL_TRUE : GL_FALSE,
				layout.stride(),
				(const void*)object.m_offset
			);
			++idx;
			GON_INFO("[VBO '{0}' component moved to VAO] now is into a Shader.", object.m_name);
		}
		
		// m_vbo_vec.push_back(std::move(vbo));		
		m_vbo = std::move(vbo);
	}

	void OpenglVAO::takeEBO(u_ptr<EBO>& _ebo)
	{
		GON_INFO("[EBO component moved to VAO] now is into a Shader.");
		m_ebo = std::move(_ebo);
		glBindVertexArray(m_id_vao);
		m_ebo->bind();
	}

}