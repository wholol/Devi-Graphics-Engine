#include "RenderBuffer.h"
#include "glad/glad.h"

namespace Devi
{

	void RenderBuffer::CreateRenderBuffer(GLenum internalformat, int height, int width)
	{
		glGenRenderbuffers(1, &m_renderBufferID);
		glBindRenderbuffer(GL_RENDERBUFFER, m_renderBufferID);
		glRenderbufferStorage(GL_RENDERBUFFER, internalformat, width, height);
	}

	void RenderBuffer::Bind()
	{
		glBindRenderbuffer(GL_RENDERBUFFER, m_renderBufferID);
	}

	void RenderBuffer::UnBind()
	{
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}
	int RenderBuffer::GetID() const
	{
		return m_renderBufferID;
	}
}

