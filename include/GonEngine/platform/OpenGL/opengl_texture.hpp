#pragma once
#include "GonEngine/renderer/texture.hpp"
#include "GonEngine/platform/OpenGL/opengl_shader.hpp"

namespace Gon {


	class OpenGLTexture2D : public Texture2D
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

		OpenGLTexture2D(const std::string& path, Texture2D::Format format);
		OpenGLTexture2D(uint32_t width, uint32_t height);
		virtual ~OpenGLTexture2D();

		virtual uint32_t getWidth()  const override { return m_width; };
		virtual uint32_t getHeight() const override { return m_height; };

		virtual void bind(uint32_t unit) const override;

		virtual void setData(void* data, uint32_t size) override;
		virtual uint32_t getTextureID() const override { return m_textID; }


		void setWrap(Wrap s, Wrap t);
		void setFilter(Filter mag, Filter min, Filter mipMapMag = Filter::None, Filter mipMapMin = Filter::None);

	private:
		void applyWrapping() const;
		void applyFilter() const;
	private:

		const std::string m_path;

		OpenGLTexture2D::Format m_format = OpenGLTexture2D::Format::RGB;

		uint32_t m_width	= 0;
		uint32_t m_height	= 0;
		uint32_t m_depth	= 0; // channels

		uint32_t m_textID;

		std::pair<Wrap, Wrap> m_wrap
		{
			Wrap::Repeat,
			Wrap::Repeat
		};
		std::pair<Filter, Filter> m_filter
		{
			Filter::Linear,
			Filter::Linear
		};
		std::pair<Filter, Filter> m_filterMipMap
		{
			Filter::None,
			Filter::None
		};

		GLenum m_internalFormat;
		GLenum m_dataFormat;
	};



}