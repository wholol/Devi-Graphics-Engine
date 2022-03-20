#include "Scene.h"

namespace Devi
{
	void Scene::SetProjectionMatrixParams(ProjectionMatrixParams projectionMatrixParams)
	{
		m_projectionMatrix = glm::perspective(glm::radians(projectionMatrixParams.FieldOfViewY), static_cast<float>(projectionMatrixParams.screenWidth) / static_cast<float>(projectionMatrixParams.screenHeight), projectionMatrixParams.zNear, projectionMatrixParams.zFar);
	}

	void Scene::Update(GLFWwindow* window, double deltaTime)
	{
		const auto& viewMatrix = m_camera.getViewMatrix();
		auto viewProjectionMatrix = m_projectionMatrix * viewMatrix;

		Renderer::UpdateViewProjectionMatrix(viewProjectionMatrix);
		
		m_camera.Update(window, deltaTime);

		//for each drawable
		//update the drawable
		//insdie each drawable-> bind the shader.
		
	}
}

