#pragma once
#include "../src/FrameBuffer.h"
#include "../src/Texture2D.h"
#include "../src/Shader.h"
#include "Math/glm/glm.hpp"
#include "../src/Renderer.h"
#include "../src/Camera.h"
#include "glad/glad.h"
#include "../src/IDrawable.h"
#include "../src/ShaderManager.h"

namespace Devi
{
	struct ShadowMapLightSpaceMatrixParams
	{
		double left;
		double right;
		double top;
		double bottom;
		double zNear;
		double zFar;

		glm::vec3 directionalLightPosition = glm::vec3(0.0f,800.0f,0.0f);
		glm::vec3 directionalLightDirection = glm::vec3(0.0, -0.67, -0.99);
	};
	/**
	* Shadow Map class that uses directional lights.
	*/
	class ShadowMapRenderer
	{
		public:

			ShadowMapRenderer(int shadowMapWidth, int shadowMapHeight, ShadowMapLightSpaceMatrixParams params,std::shared_ptr<ShaderManager> shaderManager);
			void RenderDepthMap(const std::vector<DrawablePtr>& drawables);
			glm::mat4 GetLightSpaceMatrix() const;
			std::shared_ptr<Texture2D> GetDepthMap() const;
		private:
			FrameBuffer m_framebuffer;
			int m_shadowMapWidth;
			int m_shadowMapHeight;
			std::shared_ptr<Texture2D> m_depthTexture;
			std::shared_ptr<Shader> m_depthMapShader;
			std::shared_ptr<ShaderManager> m_shaderManager;
			glm::mat4 m_lightViewMatrix{ glm::mat4(1.0) };
			glm::mat4 m_lightOrthoMatrix{ glm::mat4(1.0) };
			glm::vec3 m_directionalLightPos{ glm::vec3(0.0, 100.0, 0.0) };
	};
}
