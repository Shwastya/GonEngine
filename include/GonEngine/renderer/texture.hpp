#pragma once
#include "GonEngine/memcfg/scp_ptr.hpp"

namespace Gon {


	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t getWidth() const = 0;
		virtual uint32_t getHeight() const = 0;

		virtual void setData(void* data, uint32_t size) = 0;
		virtual uint32_t getTextureID() const = 0;

		virtual void bind(const uint32_t unit = 0) const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		enum  class Format
		{
			RGB,
			RGBA
		};

		static u_ptr<Texture2D> create(const std::string& path, Texture2D::Format format);
		static u_ptr<Texture2D> create(const uint32_t width, const uint32_t height);		
	};
}