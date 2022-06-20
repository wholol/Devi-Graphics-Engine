#include "..\RenderPasses\WaterRenderPass.h"

namespace Devi
{
	WaterRenderPass::WaterRenderPass(int textureWidth, int textureHeight, int quadTextureWidth, int quadTextureHeight)
		:m_textureWidth(textureWidth),
		m_textureHeight(textureHeight),
		m_quadTextureWidth(quadTextureWidth),
		m_quadTextureHeight(quadTextureHeight)
	{
		m_reflectionTexture = std::make_shared<Texture2D>("reflectionTexture");
		m_reflectionTexture->CreateEmptyTexture2D(GL_RGB, textureHeight, textureWidth, GL_RGB, GL_UNSIGNED_BYTE);
		m_reflectionTexture->AddTextureParameteri(GL_TEXTURE_WRAP_S, GL_LINEAR);
		m_reflectionTexture->AddTextureParameteri(GL_TEXTURE_WRAP_T, GL_LINEAR);

		m_reflectionFrameBuffer = std::make_shared<FrameBuffer>("reflectionFrameBuffer");
		m_reflectionFrameBuffer->AttachTexture2DToFrameBuffer(GL_COLOR_ATTACHMENT0, m_reflectionTexture, 0);

		glDrawBuffer(GL_COLOR_ATTACHMENT0);

		m_refractionTexture = std::make_shared<Texture2D>("refractionTexture");
		m_reflectionTexture->CreateEmptyTexture2D(GL_RGB, textureHeight, textureWidth, GL_RGB, GL_UNSIGNED_BYTE);
		m_reflectionTexture->AddTextureParameteri(GL_TEXTURE_WRAP_S, GL_LINEAR);
		m_reflectionTexture->AddTextureParameteri(GL_TEXTURE_WRAP_T, GL_LINEAR);

		m_refractionFrameBuffer = std::make_shared<FrameBuffer>("refractionFrameBuffer");
		m_refractionFrameBuffer->AttachTexture2DToFrameBuffer(GL_COLOR_ATTACHMENT0, m_refractionTexture, 0);

		glDrawBuffer(GL_COLOR_ATTACHMENT0);

	}
	void WaterRenderPass::Execute()
	{
		//first step
		m_reflectionFrameBuffer->Bind();
		m_reflectionFrameBuffer->SetViewPort(m_textureWidth, m_textureHeight);
		
	}
}

