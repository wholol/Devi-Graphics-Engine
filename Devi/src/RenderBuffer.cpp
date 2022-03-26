#include "RenderBuffer.h"
#include "glad/glad.h"

namespace Devi
{
	RenderBuffer::RenderBuffer(int screenWidth, int screenHeight)
	{
		glGenRenderbuffers(1, &m_renderBufferID);
		glBindRenderbuffer(GL_RENDERBUFFER, m_renderBufferID);
		//TODO needs to be mroe versatile for the components, we need params.
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, screenWidth, screenHeight);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_renderBufferID);
	}

	void RenderBuffer::Bind()
	{
		glBindRenderbuffer(GL_RENDERBUFFER, m_renderBufferID);
	}

	void RenderBuffer::UnBind()
	{
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}
}

