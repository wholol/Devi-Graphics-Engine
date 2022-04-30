#include "WaterRenderPass.h"

namespace Devi
{
	WaterRenderPass::WaterRenderPass(int textureWidth, int textureHeight, const std::vector<DrawablePtr>& drawables)
		:m_textureWidth(textureWidth),
		m_textureHeight(textureHeight),
		m_drawables(drawables)
	{
		m_reflectionTexture = std::make_shared<Texture2D>("reflectionTexture");
		m_reflectionTexture->CreateEmptyTexture2D(GL_RGB, textureHeight, textureWidth, GL_RGB, GL_UNSIGNED_BYTE);
		m_reflectionTexture->AddTextureParameteri(GL_TEXTURE_WRAP_S, GL_LINEAR);
		m_reflectionTexture->AddTextureParameteri(GL_TEXTURE_WRAP_T, GL_LINEAR);
		
		m_refractionTexture = std::make_shared<Texture2D>("refractionTexture");
		m_reflectionTexture->CreateEmptyTexture2D(GL_RGB, textureHeight, textureWidth, GL_RGB, GL_UNSIGNED_BYTE);
		m_reflectionTexture->AddTextureParameteri(GL_TEXTURE_WRAP_S, GL_LINEAR);
		m_reflectionTexture->AddTextureParameteri(GL_TEXTURE_WRAP_T, GL_LINEAR);


		m_waterReflectionFrameBuffer.AttachTexture2DToFrameBuffer(GL_COLOR_ATTACHMENT0, *m_reflectionTexture, 0);
		m_waterRefractionFrameBuffer.AttachTexture2DToFrameBuffer(GL_COLOR_ATTACHMENT0, *m_refractionTexture, 0);

		glDrawBuffer(GL_COLOR_ATTACHMENT0);
	}

	void WaterRenderPass::execute()
	{
		glViewport(0, 0, m_textureWidth, m_textureHeight);

		for (const auto& drawable : m_drawables)
		{

		}
	}
}

