#pragma once
#include "GonEngine/renderer/texture.hpp"

typedef unsigned int GLenum;

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

		virtual uint32_t getWidth()  const override { return m_width;  };
		virtual uint32_t getHeight() const override { return m_height;  };

		virtual void bind(uint32_t unit) const override;

		virtual void setData(void* data, uint32_t size) override;
		virtual uint32_t getTextureID() const override { return m_textID; }

		virtual void  setTilingScale(const float scale) override { m_scale = scale; };
		virtual const float getTilingScale() const		override { return m_scale; }; // hasta 255

		void setWrap(Wrap s, Wrap t);
		void setFilter(Filter mag, Filter min, Filter mipMapMag = Filter::None, Filter mipMapMin = Filter::None);

	private:
		void applyWrapping() const;
		void applyFilter() const;
	private:

		const std::string m_path;

		OpenGLTexture2D::Format m_format = OpenGLTexture2D::Format::RGB;

		uint32_t m_width	{ 0 };
		uint32_t m_height	{ 0 };
		uint32_t m_depth	{ 0 };	// channels
		float  m_scale		{ 1.0f };	// hasta 255

		uint32_t m_textID;
		

		std::pair<Wrap, Wrap> m_wrap
		{
			Wrap::Repeat,
			Wrap::Repeat
		};
		std::pair<Filter, Filter> m_filter
		{
			Filter::Linear,
			Filter::None
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