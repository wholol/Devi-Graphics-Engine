#include "Scene.h"

namespace Devi
{
	void Scene::SetProjectionMatrixParams(ProjectionMatrixParams projectionMatrixParams)
	{
		m_projectionMatrix = glm::perspective(glm::radians(projectionMatrixParams.fieldOfViewY), static_cast<float>(projectionMatrixParams.screenWidth) / static_cast<float>(projectionMatrixParams.screenHeight), projectionMatrixParams.zNear, projectionMatrixParams.zFar);
		Renderer::SetRendererProjectionMatrix(m_projectionMatrix);
	}
	
	void Scene::Update(double deltaTime)
	{		
		m_camera.Update(deltaTime);

		const auto& viewMatrix = m_camera.getViewMatrix();

		Renderer::UpdateViewMatrix(viewMatrix);

		m_cube.Draw();

		for (const auto& drawable : m_drawables)
		{
			drawable->Draw();
		}
	}

	void Scene::AddDrawable(DrawablePtr drawable)
	{
		m_drawables.emplace_back(drawable);
	}

	void Scene::ClearScene()
	{
		Renderer::Clear();	//Note: do not call clear after the draw call for drawables, as the swap buffers occurs after the the draw calls.
	}
}

