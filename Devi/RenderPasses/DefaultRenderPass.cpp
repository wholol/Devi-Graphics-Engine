#include "DefaultRenderPass.h"
#include "../src/BindingLocation.h"

namespace Devi
{
	DefaultRenderPass::DefaultRenderPass()
	{

	}
	void DefaultRenderPass::Execute()
	{

		glViewport(0, 0, 1920, 1080);		//TODO use application screenwidth and not hardcode the value

		auto shadowMapPass = m_dependencyRenderPasses.find(RenderPassType::ShadowMap);

		auto shadowMapRenderPass = std::dynamic_pointer_cast<ShadowMapRenderPass>(shadowMapPass->second);
		
		auto depthMap = shadowMapRenderPass->GetFrameBuffer("shadowMapFrameBuffer")->GetTextureAttachment();
		
		auto& lightSpaceMatrix = shadowMapRenderPass->GetLightSpaceMatrix();

		//step 1
		{
			for (auto& renderOp : GetStep(0).renderQueue)
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
}

