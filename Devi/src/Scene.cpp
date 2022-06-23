#include "Scene.h"

namespace Devi
{
	Scene::Scene(Assets& assets, int screenWidth, int screenHeight, std::shared_ptr<RenderPassManager> renderPassManager)
		: m_renderPassManager(renderPassManager)
	{
		Renderer::EnableDepthTest();
		m_drawables = assets.GetDrawables();
		m_shaderManager = assets.GetShaderManager();	
		m_camera.SetPosition(glm::vec3(0.0f, 500.0f ,200.0f));
	}

	void Scene::SetProjectionMatrixParams(ProjectionMatrixParams projectionMatrixParams)
	{
		m_projectionMatrix =  glm::perspective(glm::radians(projectionMatrixParams.fieldOfViewY), static_cast<float>(projectionMatrixParams.screenWidth) / static_cast<float>(projectionMatrixParams.screenHeight), projectionMatrixParams.zNear, projectionMatrixParams.zFar);
		//m_projectionMatrix = glm::ortho(-1000.0f, 1000.0f, -1000.0f, 1000.0f, -1000.0f, 1000.0f);
		Renderer::SetRendererProjectionMatrix(m_projectionMatrix);
		m_screenWidth = projectionMatrixParams.screenWidth;
		m_screenHeight = projectionMatrixParams.screenHeight;
	}
	
	void Scene::Update(double deltaTime)
	{		
		
		const auto& viewMatrix = m_camera.GetViewMatrix();
		const auto& waterReflectionViewMatrix = m_camera.GetWaterReflectionViewMatrix();

		Renderer::SetRendererViewMatrix(viewMatrix);
		Renderer::SetWaterReflectionViewMatrix(waterReflectionViewMatrix);
		
		m_renderPassManager->ExecutePasses();
		
		m_camera.Update(deltaTime);
	}

	void Scene::ClearScene()
	{
		Renderer::Clear();	//Note: do not call clear after the draw call for drawables, as the swap buffers occurs after the the draw calls.
	}
}

