#pragma once
#include "RenderPass.h"
#include "../src/Texture2D.h"
#include "Math/glm/gtc/matrix_transform.hpp"
#include "../Light/Light.h"
#include "../Light/DirectionalLight.h"

namespace Devi
{
	struct ShadowMapOrthoMatrixParams
	{
		double left;
		double right;
		double top;
		double bottom;
		double zNear;
		double zFar;
	};

	class ShadowMapRenderPass : public RenderPass
	{
	public:
		ShadowMapRenderPass(int shadowMapTextureWidth, int shadowMapTextureHeight, 
			ShadowMapOrthoMatrixParams params, std::shared_ptr<DirectionalLight> directionalLight);
		void Execute() override;
		std::shared_ptr<Texture2D> GetDepthMap() const;

	private:
		
		int m_shadowMapTextureWidth;
		int m_shadowMapTextureHeight;

		std::shared_ptr<DirectionalLight> m_directionalLight;
		
		FrameBuffer m_framebuffer{ "ShadowMap" };	
		std::shared_ptr<Texture2D> m_depthTexture;
		
		glm::mat4 m_lightViewMatrix{ glm::mat4(1.0) };
		glm::mat4 m_lightOrthoMatrix{ glm::mat4(1.0) };
	};
}