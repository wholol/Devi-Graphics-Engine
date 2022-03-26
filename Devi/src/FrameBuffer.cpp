#include "FrameBuffer.h"
#include <glad/glad.h>

namespace Devi
{
	FrameBuffer::FrameBuffer()
	{
		glGenFramebuffers(1, &m_frameBufferID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferID);
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

