#include "Texture2DFrameBuffer.h"
#include "glad/glad.h"

Devi::Texture2DFrameBuffer::Texture2DFrameBuffer()
{
}

void Devi::Texture2DFrameBuffer::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_texture2DFrameBufferID);
}

void Devi::Texture2DFrameBuffer::UnBind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

