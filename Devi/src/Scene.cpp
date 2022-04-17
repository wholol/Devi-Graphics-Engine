#include "Scene.h"

namespace Devi
{
	Scene::Scene(Assets& assets)
	{
		Renderer::EnableDepthTest();
		m_drawables = assets.GetDrawables();
	}

	void Scene::SetProjectionMatrixParams(ProjectionMatrixParams projectionMatrixParams)
	{
		m_projectionMatrix = glm::perspective(glm::radians(projectionMatrixParams.fieldOfViewY), static_cast<float>(projectionMatrixParams.screenWidth) / static_cast<float>(projectionMatrixParams.screenHeight), projectionMatrixParams.zNear, projectionMatrixParams.zFar);
		Renderer::SetRendererProjectionMatrix(m_projectionMatrix);
		m_screenWidth = projectionMatrixParams.screenWidth;
		m_screenHeight = projectionMatrixParams.screenHeight;
	}
	
	void Scene::Update(double deltaTime)
	{		
		m_camera.Update(deltaTime);

		const auto& viewMatrix = m_camera.getViewMatrix();
		
		Renderer::UpdateViewMatrix(viewMatrix);

		for (const auto& drawable : m_drawables)
		{
			drawable->Draw();
		}
	}

	void Scene::ClearScene()
	{
		Renderer::Clear();	//Note: do not call clear after the draw call for drawables, as the swap buffers occurs after the the draw calls.
	}
}

