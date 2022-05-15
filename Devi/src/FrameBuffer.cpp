#include "FrameBuffer.h"

namespace Devi
{
	FrameBuffer::FrameBuffer(const std::string& name)
		:m_name(name)
	{
		glGenFramebuffers(1, &m_frameBufferID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferID);
	}

	void FrameBuffer::AttachRenderBufferToFrameBuffer(GLint attachment, std::shared_ptr<RenderBuffer> renderBuffer)
	{
		Bind();
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, renderBuffer->GetID());
		m_renderBufferAttachment = renderBuffer;
	}

	void FrameBuffer::AttachTexture2DToFrameBuffer(GLint attachment, std::shared_ptr<Texture2D> texture, int level)
	{
		Bind();
		glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, texture->GetID(), level);
		m_textureAttachment = texture;
	}

	void FrameBuffer::SetViewPort(int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void FrameBuffer::ClearFrameBufferDepth()
	{
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	void FrameBuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferID);
	}

	void FrameBuffer::UnBind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	std::shared_ptr<ITexture> FrameBuffer::GetTextureAttachment() const
	{
		return m_textureAttachment;
	}

	std::shared_ptr<RenderBuffer> FrameBuffer::GetRenderBufferAttachment() const
	{
		return m_renderBufferAttachment;
	}

	std::string FrameBuffer::GetName() const
	{
		return m_name;
	}

	FrameBuffer::~FrameBuffer()
	{
		glDeleteFramebuffers(1, &m_frameBufferID);
	}
}

