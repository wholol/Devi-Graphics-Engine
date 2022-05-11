#include "Scene.h"

namespace Devi
{
	Scene::Scene(Assets& assets, int screenWidth, int screenHeight, std::shared_ptr<RenderPassManager> renderPassManager)
		: m_renderPassManager(renderPassManager)
	{
		Renderer::EnableDepthTest();
		m_drawables = assets.GetDrawables();
		m_shaderManager = assets.GetShaderManager();	
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
		m_camera.Update(deltaTime);

		const auto& viewMatrix = m_camera.getViewMatrix();
		
		m_renderPassManager->ExecutePasses();

		glViewport(0, 0, m_screenWidth, m_screenHeight);

		Renderer::SetRendererViewMatrix(viewMatrix);
		Renderer::SetRendererProjectionMatrix(m_projectionMatrix);
	}

	void Scene::ClearScene()
	{
		Renderer::Clear();	//Note: do not call clear after the draw call for drawables, as the swap buffers occurs after the the draw calls.
	}
}

