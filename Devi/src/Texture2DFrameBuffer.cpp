#include "Texture2DFrameBuffer.h"

void Devi::Texture2DFrameBuffer::SetTexParameters(GLenum pname, GLint param)
{
	glTexParameteri(GL_TEXTURE_2D, pname, param);
}

void Devi::Texture2DFrameBuffer::AttachTextureToFrameBuffer(GLenum attachment, GLenum texTarget)
{
	glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, texTarget, m_texture2DFrameBufferID, 0);
}

void Devi::Texture2DFrameBuffer::Bind(unsigned int activeTexture)
{
	glActiveTexture(GL_TEXTURE0 + activeTexture);
	glBindTexture(GL_TEXTURE_2D, m_texture2DFrameBufferID);
}

void Devi::Texture2DFrameBuffer::UnBind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

