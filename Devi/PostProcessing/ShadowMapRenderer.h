#pragma once
#include "../src/FrameBuffer.h"
#include "../src/Texture2D.h"
#include "../src/Shader.h"
#include "Math/glm/glm.hpp"
#include "../src/Renderer.h"
#include "../src/Camera.h"
#include "glad/glad.h"

namespace Devi
{
	/**
	* Shadow Map class that uses directional lights.
	*/
	class ShadowMapRenderer
	{
		public:
			ShadowMapRenderer(int shadowMapWidth, int shadowMapHeight);
			void RenderDepthMap();

		private:
			FrameBuffer m_framebuffer;
			Texture2D m_depthTexture;
			Shader m_depthMapShader;
			glm::mat4 m_lightViewMatrix{ glm::mat4(1.0) };
			glm::mat4 m_lightOrthoMatrix{ glm::mat4(1.0) };
			glm::vec3 m_directionalLightPos{ glm::vec3(0.0, 100.0, 0.0) };
	};
}
