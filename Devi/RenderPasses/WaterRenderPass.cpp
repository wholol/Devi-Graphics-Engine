#include "..\RenderPasses\WaterRenderPass.h"

namespace Devi
{
	WaterRenderPass::WaterRenderPass(int textureWidth, int textureHeight)
		:m_textureWidth(textureWidth),
		m_textureHeight(textureHeight)
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
		//first step: render refraction texture
		m_refractionFrameBuffer->Bind();
		m_refractionFrameBuffer->SetViewPort(m_textureWidth, m_textureHeight);
		
		//step 1: refraction texture
		{
			for (auto& renderOp : GetStep(0).renderQueue)
			{
				renderOp.shader->Bind();

				//bind refraction plane
				renderOp.shader->SetUniform("clippingPlane", glm::vec4(0, 1, 0, 0), UniformDataType::VEC4);

				if (renderOp.material)
				{
					renderOp.material->Bind(renderOp.shader);
				}

				for (const auto& texturePairs : renderOp.textures)
				{
					auto texture = texturePairs.first;
					unsigned int ActiveTextureID = texturePairs.second;
					texture->Bind(ActiveTextureID);
				}

				renderOp.shader->SetUniform("modelMatrix", renderOp.drawable->GetModelMatrix(), UniformDataType::MAT4);
				renderOp.shader->SetUniform("viewMatrix", Renderer::GetRendererViewMatrix(), UniformDataType::MAT4);	//uniform buffer
				renderOp.shader->SetUniform("projectionMatrix", Renderer::GetRendererProjectionMatrix(), UniformDataType::MAT4);	//uniform buffer

				renderOp.drawable->Draw();
			}
		}

		//second step: render reflection texture
		m_reflectionFrameBuffer->Bind();
		m_reflectionFrameBuffer->SetViewPort(m_textureWidth, m_textureHeight);

		//step 2: reflection texture
		{
			for (auto& renderOp : GetStep(1).renderQueue)
			{
				renderOp.shader->Bind();

				//bind reflection plane
				//renderOp.shader->SetUniform("plane", glm);
				renderOp.shader->SetUniform("clippingPlane", glm::vec4(0, -1, 0, 0), UniformDataType::VEC4);

				if (renderOp.material)
				{
					renderOp.material->Bind(renderOp.shader);
				}

				for (const auto& texturePairs : renderOp.textures)
				{
					auto texture = texturePairs.first;
					unsigned int ActiveTextureID = texturePairs.second;
					texture->Bind(ActiveTextureID);
				}

				renderOp.shader->SetUniform("modelMatrix", renderOp.drawable->GetModelMatrix(), UniformDataType::MAT4);
				renderOp.shader->SetUniform("viewMatrix", Renderer::GetRendererWaterReflectionViewMatrix(), UniformDataType::MAT4);	//uniform buffer
				renderOp.shader->SetUniform("projectionMatrix", Renderer::GetRendererProjectionMatrix(), UniformDataType::MAT4);	//uniform buffer

				renderOp.drawable->Draw();
			}
		}
		
		m_refractionFrameBuffer->UnBind();
	}
}

