#pragma once
#include "RenderPass.h"
#include "Texture2D.h"
#include "Math/glm/gtc/matrix_transform.hpp"

namespace Devi
{
	struct ShadowMapMatrixParams
	{
		double left;
		double right;
		double top;
		double bottom;
		double zNear;
		double zFar;

		glm::vec3 directionalLightPosition = glm::vec3(0.0f, 800.0f, 0.0f);
		glm::vec3 directionalLightDirection = glm::vec3(0.0, -0.67, -0.99);
	};

	class ShadowMapRenderPass : public RenderPass
	{
	public:
		ShadowMapRenderPass(int shadowMapTextureWidth, int shadowMapTextureHeight, ShadowMapMatrixParams params);
		void Execute() override;
		std::shared_ptr<Texture2D> GetDepthMap() const;

	private:
		int m_shadowMapTextureWidth, m_shadowMapTextureHeight;
		FrameBuffer m_framebuffer{ "ShadowMap" };
		std::shared_ptr<Texture2D> m_depthTexture;
		glm::mat4 m_lightViewMatrix{ glm::mat4(1.0) };
		glm::mat4 m_lightOrthoMatrix{ glm::mat4(1.0) };
		glm::mat4 m_modelMatrix{ glm::mat4(1.0) };
		glm::vec3 m_directionalLightPos{ glm::vec3(0.0, 100.0, 0.0) };
	};
}