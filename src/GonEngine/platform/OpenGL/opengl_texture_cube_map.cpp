#include "GonEngine/platform/OpenGL/opengl_texture_cube_map.hpp"
#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/log.hpp"
#include <glad/glad.h>
#include <stb_image.h>

namespace Gon {

	static uint32_t format2GL(OpenGLCubeMapText::Format format)
	{
		switch (format)
		{
		case OpenGLCubeMapText::Format::RGB: return GL_RGB;
		case OpenGLCubeMapText::Format::RGBA: return GL_RGBA;
		default: return GL_RGB;
		};
	}
	OpenGLCubeMapText::OpenGLCubeMapText(const std::vector<std::string>& path, OpenGLCubeMapText::Format format)
		: m_path(path), m_format(format)
	{
		stbi_set_flip_vertically_on_load(false);

		glGenTextures(1, &m_textID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_textID);				

		int32_t width = 0, height = 0, depth = 0;

		for (uint32_t i = 0; i < path.size(); i++)
		{
			
			unsigned char* data = stbi_load(path[i].c_str(), &width, &height, &depth, 0);

			m_width  = static_cast<uint32_t>(width);
			m_height = static_cast<uint32_t>(width);
			m_depth  = static_cast<uint32_t>(depth);

			GLenum colorMode{ GL_RED };

			if (depth == 3) colorMode = GL_RGB;
			else if (depth == 4) colorMode = GL_RGBA;

			if (data)
			{
				/*glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
					0,format2GL(m_format), width, width, 0,format2GL(m_format),GL_UNSIGNED_BYTE, data);
				stbi_image_free(data);*/

				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
					0, colorMode, width, width, 0, colorMode, GL_UNSIGNED_BYTE, data);
				stbi_image_free(data);
				GON_TRACE("[CREATED] Loaded cubemap texture: {0}", path[i]);
			}
			else GON_ERROR("Failed to load cubemap texture: {0}.", path[i]);
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);


		//glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

	OpenGLCubeMapText::~OpenGLCubeMapText()
	{
		GON_TRACE("[DESTROYED] Cubemap texture id: {0}.", m_textID);
		glDeleteTextures(1, &m_textID);
	}

	void OpenGLCubeMapText::bind(uint32_t unit) const
	{
		
		//glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_textID);
	}
}