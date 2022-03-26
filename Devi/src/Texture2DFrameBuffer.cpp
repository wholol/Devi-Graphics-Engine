#include "Texture2DFrameBuffer.h"

namespace Devi
{
	Texture2DFrameBuffer::Texture2DFrameBuffer(int screenWidth, int screenHeight)
		: m_screenWidth(screenWidth),
		  m_screenHeight(screenHeight)
	{
		m_frameBuffer.Bind();
		m_renderBuffer.Bind();
		m_texture2D.Bind();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_screenWidth, m_screenHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture2DFrameBufferID, 0);
	}


	void Texture2DFrameBuffer::Bind()
	{
		m_frameBuffer.Bind();
	}

	void Texture2DFrameBuffer::UnBind()
	{
		m_frameBuffer.UnBind();
	}
}
