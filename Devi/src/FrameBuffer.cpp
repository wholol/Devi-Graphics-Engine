#include "FrameBuffer.h"

namespace Devi
{
	FrameBuffer::FrameBuffer()
	{
		glGenFramebuffers(1, &m_frameBufferID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferID);
	}

	void FrameBuffer::AttachRenderBufferToFrameBuffer(GLint attachment, RenderBuffer& renderBuffer)
	{
		Bind();
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, renderBuffer.GetID());
	}

	void FrameBuffer::AttachTexture2DToFrameBuffer(GLint attachment, Texture2D& texture, int level)
	{
		Bind();
		glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, texture.GetID(), level);
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
	FrameBuffer::~FrameBuffer()
	{
		glDeleteFramebuffers(1, &m_frameBufferID);
	}
}

