#include "Texture2DFrameBuffer.h"

namespace Devi
{

	void Texture2DFrameBuffer::SetTexParameters(GLenum pname, GLint param)
	{
		glTexParameteri(GL_TEXTURE_2D, pname, param);
	}

	void Texture2DFrameBuffer::AttachTextureToFrameBuffer(GLenum attachment, GLenum texTarget)
	{
		glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, texTarget, m_texture2DFrameBufferID, 0);
	}

	void Texture2DFrameBuffer::Bind(unsigned int activeTexture)
	{
		glActiveTexture(GL_TEXTURE0 + activeTexture);
		glBindTexture(GL_TEXTURE_2D, m_texture2DFrameBufferID);
	}

	void Texture2DFrameBuffer::UnBind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
