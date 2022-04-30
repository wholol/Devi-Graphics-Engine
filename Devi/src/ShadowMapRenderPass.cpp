#include "ShadowMapRenderPass.h"

namespace
{
	float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	static constexpr glm::vec3 GlobalUpVector = glm::vec3(0.0f, 1.0f, 0.0f);
}

namespace Devi
{
	ShadowMapRenderPass::ShadowMapRenderPass(int shadowMapTextureWidth, int shadowMapTextureHeight, ShadowMapMatrixParams params)
		: m_shadowMapTextureWidth(shadowMapTextureWidth),
		m_shadowMapTextureHeight(shadowMapTextureHeight)
	{
		m_depthTexture = std::make_shared<Texture2D>("sceneDepthMap");
		m_depthTexture->CreateEmptyTexture2D(GL_DEPTH_COMPONENT, m_shadowMapTextureHeight, m_shadowMapTextureWidth, GL_DEPTH_COMPONENT, GL_FLOAT);
		m_depthTexture->AddTextureParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		m_depthTexture->AddTextureParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		m_depthTexture->AddTextureParameteri(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		m_depthTexture->AddTextureParameteri(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		m_depthTexture->AddTextureParameterfv(GL_TEXTURE_BORDER_COLOR, borderColor);
		m_framebuffer.AttachTexture2DToFrameBuffer(GL_DEPTH_ATTACHMENT, *m_depthTexture, 0);

		//learnopengl : framebuffers are not compelete without color buffers, we need to explcitly tell opengl we dont need it.
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);

		auto m_cameraLookAtDirection = glm::normalize(params.directionalLightPosition - params.directionalLightDirection);
		auto m_cameraRightVector = glm::cross(GlobalUpVector, m_cameraLookAtDirection);
		auto m_cameraUpVector = glm::cross(m_cameraLookAtDirection, m_cameraRightVector);

		m_lightOrthoMatrix = glm::ortho(params.left, params.right, params.bottom, params.top, params.zNear, params.zFar);
		const glm::vec3 rightVector = glm::cross(GlobalUpVector, -params.directionalLightDirection);
		const glm::vec3 upVector = glm::cross(-params.directionalLightDirection, rightVector);
		m_lightViewMatrix = glm::lookAt(params.directionalLightPosition, params.directionalLightPosition + params.directionalLightDirection, m_cameraUpVector);
		m_modelMatrix = glm::translate(m_modelMatrix, glm::vec3(0.0f, 200.0f, -200.0f));
		m_modelMatrix = glm::scale(m_modelMatrix, glm::vec3(50.0f, 20.0f, 20.0f));
	}

	void ShadowMapRenderPass::Execute()
	{
		Renderer::SetRendererProjectionMatrix(m_lightOrthoMatrix);
		Renderer::SetRendererViewMatrix(m_lightViewMatrix);
		
		m_framebuffer.Bind();
		m_framebuffer.SetViewPort(m_shadowMapTextureWidth, m_shadowMapTextureHeight);
		m_framebuffer.ClearFrameBufferDepth();	//depth buffer must be cleared or the texture will just be black.
		
		for (const auto& renderOp : m_renderQueue)
		{
			renderOp.shader->Bind();

			//TODO REMOVE THESE
			if (renderOp.drawable->GetName() == "BasicCube")
			{
				renderOp.shader->SetUniform("modelMatrix", m_modelMatrix, UniformDataType::MAT4);	//TODO get from drawable class
			}
			else
			{
				renderOp.shader->SetUniform("modelMatrix", glm::mat4(1.0), UniformDataType::MAT4);	//TODO get from drawable class
				renderOp.shader->SetUniform("lightSpaceMatrix", m_lightViewMatrix, UniformDataType::MAT4);
			}
			
			renderOp.shader->SetUniform("viewMatrix", m_lightViewMatrix, UniformDataType::MAT4);	//can be ubo
			renderOp.shader->SetUniform("projectionMatrix", m_lightOrthoMatrix, UniformDataType::MAT4);	//can be ubo

			//TODO SET THE UNIFORMS. (LIGHT VIEW MATRIX ETC).
			for (const auto& texturePairs : renderOp.textures)
			{
				auto texture = texturePairs.first;
				unsigned int ActiveTextureID = texturePairs.second;
				texture->Bind(ActiveTextureID);
			}

			renderOp.drawable->Draw();
		}

		m_framebuffer.UnBind();
	}

	std::shared_ptr<Texture2D> ShadowMapRenderPass::GetDepthMap() const
	{
		return m_depthTexture;
	}
}

