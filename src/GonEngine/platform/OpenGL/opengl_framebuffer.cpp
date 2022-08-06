#include "GonEngine/platform/OpenGL/opengl_framebuffer.hpp"

#include <glad/glad.h>
#include "GonEngine/gon.hpp"
#include "GonEngine/renderer/management/render_manager.hpp"
#include "GonEngine/memcfg/goncfg.h"
#include "GonEngine/log.hpp"

namespace Gon
{

	static void CheckFrameBufferStatus()
	{
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			GON_ERROR("Error, FrameBuffer Not Complete");
			return;
		}
	}

	// Create a namespace o clase especifica
	// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	static GLenum textureTarget(bool samples)
	{
		return samples ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
	}
	static GLenum renderBufferTarget(bool samples) { return samples ? GL_RENDERBUFFER_SAMPLES : GL_RENDERBUFFER; }
	
	static void createColorTexture(uint32_t* outID, uint32_t count)
	{
		glGenTextures(count, outID);
	}
	static void createRenderBuffer(uint32_t* outID, uint32_t count)
	{
		glGenRenderbuffers(count, outID);
	}
	static void bindTexture(bool samples, uint32_t id)
	{
		glBindTexture(textureTarget(samples), id);
	}
	static void BinRenderBuffer(bool samples, uint32_t id)
	{
		glBindRenderbuffer(renderBufferTarget(samples), id);
	}
	static void attachTexture(uint32_t id, int samples, GLenum interanlformat, GLenum format, uint32_t w, uint32_t h, int idx)
	{
		const bool multisampled{ samples > 1 };
		if (multisampled)
			glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, interanlformat, w, h, GL_FALSE);		
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, interanlformat, w, h, 0, format, GL_UNSIGNED_BYTE, NULL);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			glBindTexture(GL_TEXTURE_2D, 0);
		}
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + idx, textureTarget(multisampled), id, 0);
	}
	static void AttachRenderBuffer(uint32_t id, int samples, GLenum format, GLenum atachmentType, uint32_t W, uint32_t H)
	{
		const bool multisampled{ samples > 1 };
		if (multisampled)		
			glRenderbufferStorageMultisample(GL_RENDERBUFFER_SAMPLES, samples, format, W, H);		
		else
		{
			glRenderbufferStorage(GL_RENDERBUFFER, format, W, H);
			glBindRenderbuffer(GL_RENDERBUFFER, 0);
		}
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, atachmentType, renderBufferTarget(multisampled), id);
	}
	static bool isDepthFomat(const FBTextureFormat& format)
	{
		switch (format)
		{
			case FBTextureFormat::DEPTH24STENCIL8: return true;
		}
		return false;
	}


	OpenGLFrameBuffer::OpenGLFrameBuffer(const FBProps& props)
		: m_textProps(props), m_fboID(0)//, m_TextColor(0), m_RenderBuffer(0)
	{
		for (auto prop : m_textProps.List.Collection)
		{
			if (!isDepthFomat(prop.TextureFormat)) m_colorListProps.emplace_back(prop.TextureFormat);
			else m_depthBufferProp = prop.TextureFormat;
		}
		colorDepthAttachment();
	}
	OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		glDeleteFramebuffers(1, &m_fboID);
		glDeleteTextures(static_cast<GLsizei>(m_colors.size()), m_colors.data());
		glDeleteRenderbuffers(1, &m_depth);

		m_colors.clear();
		m_depth = 0;
	}
	void OpenGLFrameBuffer::bind() const
	{
		// Pinta sobre el FBO
		glBindFramebuffer(GL_FRAMEBUFFER, m_fboID);
		RenderCall::setViewPort(0, 0, m_textProps.Width, m_textProps.Height);
	}
	void OpenGLFrameBuffer::unbind() const
	{
		// Deja de pintar spbre el FBO
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	void OpenGLFrameBuffer::activeTexture(uint32_t idx) const
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_colors[idx]);
	}
	void OpenGLFrameBuffer::resize(uint32_t width, uint32_t height)
	{
		m_textProps.Width = width;
		m_textProps.Height = height;
		colorDepthAttachment();
	}
	int OpenGLFrameBuffer::readPixel(uint32_t attachmentIdx, int x, int y)
	{
		glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIdx);
		int pixelData;
		glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData);
		return pixelData;
	}
	void OpenGLFrameBuffer::colorDepthAttachment()
	{
		if (m_fboID)
		{
			glDeleteFramebuffers(1, &m_fboID);
			glDeleteTextures(static_cast<GLsizei>(m_colors.size()), m_colors.data());
			glDeleteRenderbuffers(1, &m_depth);

			m_colors.clear();
			m_depth = 0;
		}
		// generar el FBO
		glGenFramebuffers(1, &m_fboID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_fboID);

		bool isMultiSample = m_textProps.Samples > 1;
		// generar textura color // COLLECTIONS
		if (m_colorListProps.size())
		{
			m_colors.resize(m_colorListProps.size());
			createColorTexture(m_colors.data(), static_cast<uint32_t>(m_colors.size()));

			for (uint32_t i = 0; i < m_colorListProps.size(); ++i)
			{
				bindTexture(isMultiSample, m_colors[i]);

				switch (m_colorListProps[i].TextureFormat)
				{
				case FBTextureFormat::RGBA8:
					attachTexture(m_colors[i], m_textProps.Samples, GL_RGBA8, GL_RGBA, m_textProps.Width, m_textProps.Height, i); 
					break;

				case FBTextureFormat::REDINTEGER:				
					attachTexture(m_colors[i], m_textProps.Samples, GL_R32I, GL_RED_INTEGER, m_textProps.Width, m_textProps.Height, i);
					break;
				}
			}
		}
		if (m_depthBufferProp.TextureFormat != FBTextureFormat::None)
		{
			createRenderBuffer(&m_depth, 1);
			BinRenderBuffer(isMultiSample, m_depth);

			switch (m_depthBufferProp.TextureFormat)
			{
			case FBTextureFormat::DEPTHCOMPONENT24:
				AttachRenderBuffer(m_depth, isMultiSample, GL_DEPTH_COMPONENT24, GL_DEPTH_ATTACHMENT, m_textProps.Width, m_textProps.Height);
				break;
			}
		}

		if (m_colors.size() > 1 && m_colors.size() < 5)
		{
			GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
			glDrawBuffers(static_cast<GLsizei>(m_colors.size()), buffers);
		}
		CheckFrameBufferStatus();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}