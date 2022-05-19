#include "ShadowMapRenderPass.h"

namespace
{
	float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	static constexpr glm::vec3 GlobalUpVector = glm::vec3(0.0f, 1.0f, 0.0f);
}

namespace Devi
{
	ShadowMapRenderPass::ShadowMapRenderPass(int shadowMapTextureWidth, int shadowMapTextureHeight, ShadowMapOrthoMatrixParams params, std::shared_ptr<DirectionalLight> directionalLight)
		: m_shadowMapTextureWidth(shadowMapTextureWidth),
		  m_shadowMapTextureHeight(shadowMapTextureHeight),
		  m_directionalLight(directionalLight)
	{
		m_shadowMapFrameBuffer = std::make_shared<FrameBuffer>("shadowMapFrameBuffer");
		m_frameBufferMap.insert(std::make_pair(m_shadowMapFrameBuffer->GetName(), m_shadowMapFrameBuffer));

		m_depthTexture = std::make_shared<Texture2D>("sceneDepthMap");
		m_depthTexture->CreateEmptyTexture2D(GL_DEPTH_COMPONENT, m_shadowMapTextureHeight, m_shadowMapTextureWidth, GL_DEPTH_COMPONENT, GL_FLOAT);
		m_depthTexture->AddTextureParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		m_depthTexture->AddTextureParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		m_depthTexture->AddTextureParameteri(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		m_depthTexture->AddTextureParameteri(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		m_depthTexture->AddTextureParameterfv(GL_TEXTURE_BORDER_COLOR, borderColor);
		m_shadowMapFrameBuffer->AttachTexture2DToFrameBuffer(GL_DEPTH_ATTACHMENT, m_depthTexture, 0);

		//learnopengl.com : framebuffers are not compelete without color buffers, we need to explcitly tell opengl we dont need it.
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);

		//light ortho matrix
		m_lightOrthoMatrix = glm::ortho(params.left, params.right, params.bottom, params.top, params.zNear, params.zFar);
	}

	void ShadowMapRenderPass::Execute()
	{	

		//light view matrix
		auto lightPos = m_directionalLight->GetLightPosition();
		auto lightDir = m_directionalLight->GetLightDirection();
		auto lightRightVector = glm::cross(GlobalUpVector, lightDir);
		auto lightUpVector = glm::cross(lightDir, lightRightVector);
		m_lightViewMatrix = glm::lookAt(lightPos, lightPos + lightDir, lightUpVector);

		m_shadowMapFrameBuffer->Bind();
		m_shadowMapFrameBuffer->SetViewPort(m_shadowMapTextureWidth, m_shadowMapTextureHeight);
		m_shadowMapFrameBuffer->ClearFrameBufferDepth();	//depth buffer must be cleared or the texture will just be black.
		
		//step 1
		{
			for (const auto& renderOp : GetStep(0).renderQueue)
			{
				renderOp.shader->Bind();

				renderOp.shader->SetUniform("modelMatrix", renderOp.drawable->GetModelMatrix(), UniformDataType::MAT4);
				renderOp.shader->SetUniform("viewMatrix", m_lightViewMatrix, UniformDataType::MAT4);	//can be ubo
				renderOp.shader->SetUniform("projectionMatrix", m_lightOrthoMatrix, UniformDataType::MAT4);	//can be ubo

				for (const auto& texturePairs : renderOp.textures)
				{
					auto texture = texturePairs.first;
					unsigned int ActiveTextureID = texturePairs.second;
					texture->Bind(ActiveTextureID);
				}

				renderOp.drawable->Draw();
			}

			m_shadowMapFrameBuffer->UnBind();
		}
	}
	
	const glm::mat4 ShadowMapRenderPass::GetLightSpaceMatrix() const
	{
		return m_lightOrthoMatrix * m_lightViewMatrix;
	}
}

