#include "Scene.h"

namespace Devi
{
	Scene::Scene(Assets& assets, int screenWidth, int screenHeight)
	{
		Renderer::EnableDepthTest();
		m_drawables = assets.GetDrawables();
		m_shaderManager = assets.GetShaderManager();
		ShadowMapLightSpaceMatrixParams params;
		params.top = 1000.0f;
		params.bottom = -1000.0f;
		params.left = -1000.0f;
		params.right = 1000.0f;
		params.zNear = -1000.0f;
		params.zFar = 1000.0f;
		int shadowMapScreenWidth = 800;
		int shadowMapScreenHeight = 600;
		m_shadowMapRenderer = std::make_unique<ShadowMapRenderer>(shadowMapScreenWidth, shadowMapScreenHeight,params, m_shaderManager);
		
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
		
		m_shadowMapRenderer->RenderDepthMap(m_drawables);

		glViewport(0, 0, m_screenWidth, m_screenHeight);

		Renderer::SetRendererViewMatrix(viewMatrix);
		Renderer::SetRendererProjectionMatrix(m_projectionMatrix);

		for (const auto& drawable : m_drawables)
		{
			drawable->SetShader( m_shaderManager->GetShader( drawable->GetName() ));	//set the default shader since we changed it for shadow map.
			drawable->SetDepthMapTexture(m_shadowMapRenderer->GetDepthMap());
			drawable->SetLightSpaceMatrix(m_shadowMapRenderer->GetLightSpaceMatrix());
			drawable->Draw();
		}
	}

	void Scene::ClearScene()
	{
		Renderer::Clear();	//Note: do not call clear after the draw call for drawables, as the swap buffers occurs after the the draw calls.
	}
}

