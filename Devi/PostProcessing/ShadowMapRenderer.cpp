#include "ShadowMapRenderer.h"
#include "Math/glm/gtc/matrix_transform.hpp"

namespace
{
	float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	static constexpr glm::vec3 GlobalUpVector = glm::vec3( 0.0f , 1.0f , 0.0f );
}

namespace Devi
{
	ShadowMapRenderer::ShadowMapRenderer(int shadowMapWidth, int shadowMapHeight, ShadowMapLightSpaceMatrixParams params, std::shared_ptr<ShaderManager> shaderManager)
		:
		m_shadowMapWidth(shadowMapWidth),
		m_shadowMapHeight(shadowMapHeight),
		m_shaderManager(shaderManager)
	{
		m_depthTexture = std::make_shared<Texture2D>("sceneDepthMap");
		m_depthTexture->CreateEmptyTexture2D(GL_DEPTH_COMPONENT, shadowMapHeight, shadowMapWidth, GL_DEPTH_COMPONENT, GL_FLOAT);
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

		m_lightOrthoMatrix = glm::ortho(params.left, params.right, params.bottom, params.top, params.zNear,params.zFar);
		const glm::vec3 rightVector = glm::cross(GlobalUpVector, -params.directionalLightDirection);
		const glm::vec3 upVector = glm::cross(-params.directionalLightDirection, rightVector);
		m_lightViewMatrix = glm::lookAt(params.directionalLightPosition , params.directionalLightPosition + params.directionalLightDirection, m_cameraUpVector);
	}

	void ShadowMapRenderer::RenderDepthMap(const std::vector<DrawablePtr>& drawables)
	{

		m_framebuffer.Bind();
		m_framebuffer.SetViewPort(m_shadowMapWidth, m_shadowMapHeight);
		m_framebuffer.ClearFrameBufferDepth();
		
		Renderer::SetRendererProjectionMatrix(m_lightOrthoMatrix);
		Renderer::SetRendererViewMatrix(m_lightViewMatrix);

		//for (int i = 0; i < drawables.size(); ++i)
		//{
		//	if (drawables[i]->GetName() != "DayLightSkyBox")
		//	{
		//		if (drawables[i]->GetName() == "Terrain")
		//		{
		//			auto shader = m_shaderManager->GetShader("TerrainDepthMap");
		//			drawables[i]->SetShader(shader);
		//		}
		//		else
		//		{
		//			auto shader = m_shaderManager->GetShader("DepthMap");
		//			drawables[i]->SetShader(shader);
		//		}
		//
		//		drawables[i]->Draw();
		//	}		
		//}

		m_framebuffer.UnBind();
	}

	glm::mat4 ShadowMapRenderer::GetLightSpaceMatrix() const
	{
		return m_lightOrthoMatrix * m_lightViewMatrix;
	}

	std::shared_ptr<Texture2D> ShadowMapRenderer::GetDepthMap() const
	{
		return m_depthTexture;
	}
}

