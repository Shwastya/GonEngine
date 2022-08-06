#pragma once
#include "GonEngine/renderer/framebuffer.hpp"

namespace Gon
{
	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:

		OpenGLFrameBuffer(const FBProps& spec);
		virtual ~OpenGLFrameBuffer();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual void activeTexture(uint32_t idx) const override;

		virtual void resize(uint32_t W, uint32_t H) override;
		virtual int readPixel(uint32_t attachment, int x, int y) override;

		virtual uint32_t getFBOTexture(uint32_t idx) const override { return m_colors[idx]; }
		virtual uint32_t getDepthBuffer() const override			{ return m_depth; }
		virtual const FBProps& getSpecification() const override	{ return m_textProps; };

		void colorDepthAttachment();

	private:
		uint32_t m_fboID;
		//uint32_t m_TextColor, m_RenderBuffer;

		FBProps m_textProps;

		std::vector<FBTextureProps> m_colorListProps;
		std::vector<uint32_t> m_colors;

		FBTextureProps m_depthBufferProp{ FBTextureFormat::Depth };
		uint32_t m_depth = 0;
	};
}