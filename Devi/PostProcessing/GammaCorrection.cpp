#include "GammaCorrection.h"
#include "glad/glad.h"

namespace Devi
{
	GammaCorrection::GammaCorrection(int screenWidth, int screenHeight, const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
		: m_screenWidth(screenWidth),
		  m_screenHeight(screenHeight)
	{
		m_shader.SetShaderFilePath(vertexShaderFilePath, fragmentShaderFilePath);
		
		m_renderBuffer.CreateRenderBuffer(GL_DEPTH_COMPONENT,m_screenWidth, m_screenHeight);
		
		m_framebuffer.Bind();
		m_texture2D.AddTextureParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		m_texture2D.AddTextureParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		m_texture2D.CreateEmptyTexture2D(GL_RGB, m_screenWidth, m_screenHeight, GL_RGBA, GL_UNSIGNED_BYTE);
		m_framebuffer.AttachTexture2DToFrameBuffer(GL_COLOR_ATTACHMENT0, m_texture2D, 0);
	}

	void GammaCorrection::RenderToTexture()
	{
		m_framebuffer.Bind();
		//we should pass the texture to the next post processing effect.

	}
}
