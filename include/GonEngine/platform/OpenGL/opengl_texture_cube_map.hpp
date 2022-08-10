#pragma once
#include "GonEngine/renderer/texture.hpp"

typedef unsigned int GLenum;

namespace Gon {


	class OpenGLCubeMapText : public CubeMapText
	{
	public:

		enum class Wrap
		{
			Repeat,
			Mirrored_Repeat,
			Clamp_To_Border,
			Clamp_To_Edge
		};

		enum class Filter
		{
			None,
			Nearest,
			Linear
		};

		OpenGLCubeMapText(const std::vector<std::string>& path, OpenGLCubeMapText::Format format);
		virtual ~OpenGLCubeMapText();

		virtual uint32_t getWidth () const override { return m_width; };
		virtual uint32_t getHeight() const override { return m_height; };

		virtual void bind(uint32_t unit) const override;


		virtual uint32_t getTextureID() const override { return m_textID; }
	private:

		const std::vector<std::string>& m_path;

		OpenGLCubeMapText::Format m_format = OpenGLCubeMapText::Format::RGB;

		uint32_t m_width {0};
		uint32_t m_height{0};
		uint32_t m_depth {0};	// channels
	

		uint32_t m_textID;
	};
}