#include "DefaultRenderPass.h"
#include "../src/BindingLocation.h"

namespace Devi
{
	DefaultRenderPass::DefaultRenderPass()
	{

		//m_depthTexture = std::make_shared<Texture2D>("toot");
		//m_depthTexture->CreateEmptyTexture2D(GL_RGB, 800, 600, GL_RGB, GL_FLOAT);
		//m_depthTexture->AddTextureParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//m_depthTexture->AddTextureParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//m_depthTexture->AddTextureParameteri(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		//m_depthTexture->AddTextureParameteri(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		//m_framebuffer.AttachTexture2DToFrameBuffer(GL_COLOR_ATTACHMENT0, m_depthTexture, 0);

	}
	void DefaultRenderPass::Execute()
	{
		glViewport(0, 0, 800, 600);

		auto shadowMapPass = m_dependencyRenderPasses.find(RenderPassType::ShadowMap);

		auto shadowMapRenderPass = std::dynamic_pointer_cast<ShadowMapRenderPass>(shadowMapPass->second);
		
		auto depthMap = shadowMapRenderPass->GetFrameBuffer("shadowMapFrameBuffer")->GetTextureAttachment();
		
		auto& lightSpaceMatrix = shadowMapRenderPass->GetLightSpaceMatrix();

		for (auto& renderOp : m_renderQueue)
		{
			renderOp.shader->Bind();

			//TODO: REDUNDANT BIND FOR EVERY LOOP.
			renderOp.shader->SetUniform(depthMap->GetName(), DEVI_UNIFORM_DEPTHMAP, UniformDataType::UNSIGNEDINT);

			depthMap->Bind(DEVI_UNIFORM_DEPTHMAP);

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

			renderOp.shader->SetUniform("lightSpaceMatrix", lightSpaceMatrix, UniformDataType::MAT4);	//TODO another TES for this???
			renderOp.shader->SetUniform("modelMatrix", renderOp.drawable->GetModelMatrix(), UniformDataType::MAT4);
			renderOp.shader->SetUniform("viewMatrix", Renderer::GetRendererViewMatrix(), UniformDataType::MAT4);	//uniform buffer
			renderOp.shader->SetUniform("projectionMatrix", Renderer::GetRendererProjectionMatrix(), UniformDataType::MAT4);	//uniform buffer
			
			renderOp.drawable->Draw();
		}
	}
}

