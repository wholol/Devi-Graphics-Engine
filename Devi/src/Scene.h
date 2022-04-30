#pragma once
#include "Camera.h"
#include "Window.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Math/glm/common.hpp"
#include "glfw3.h"
#include "Renderer.h"
#include "../Drawables/Cube.h"
#include "Texture2D.h"
#include "FrameBuffer.h"
#include "AssetsLoader.h"
#include "../PostProcessing/ShadowMapRenderer.h"

#include "RenderPass.h"
#include "RenderPassManager.h"
#include "ShadowMapRenderPass.h"

namespace Devi
{
	struct ProjectionMatrixParams
	{
		float fieldOfViewY;
		int screenWidth;
		int screenHeight;
		float zNear;
		float zFar;
	};

	/**
	* Scene class. responsible for updating the drawables in the scene.
	*/
	class Scene
	{
	public:
		Scene(Assets& assets, int screenWidth, int screenHeight);
		void SetProjectionMatrixParams(ProjectionMatrixParams projectionMatrixParams);
		void Update(double deltaTime);
		void ClearScene();

	private:
		std::vector<DrawablePtr> m_drawables;
		std::shared_ptr<ShaderManager> m_shaderManager;
		std::shared_ptr<TextureManager> m_textureManager;

		glm::mat4 m_projectionMatrix{glm::mat4(1.0)};
		Camera m_camera;
		std::unique_ptr<ShadowMapRenderer> m_shadowMapRenderer;
		std::unique_ptr<RenderPassManager> m_renderPassManager;
		int m_screenWidth;
		int m_screenHeight;
	};

}