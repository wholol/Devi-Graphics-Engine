#include "Application.h"
#include "BasicShapes/BasicShapesVertexData.h"
#include "Math/glm/mat4x4.hpp"
#include "Math/glm/vec3.hpp"
#include <string>
#include "Camera.h"

#include "SkyBox.h"
#include "CPUHeightMap.h"
#include "GPUHeightMap.h"

namespace Devi
{
	Application::Application(int screenWidth, int screenHeight, const std::string& title)
	{
		m_window.Init(screenWidth, screenHeight, title);	//IMPORTANT. THIS FUNCTION SHOULD BE COMPLETED BEFORE ANY GLAD CODE SHOULD BE RUN, OR THE APP CRASHES.
		m_screenWidth = screenWidth;
		m_screenHeight = screenHeight;
		
		Inputs::Init(&m_window);
		m_renderPassManager = std::make_shared<RenderPassManager>();
		m_renderPassManager->Init();
		
		m_assets = std::make_shared<Assets>(m_renderPassManager);
		m_assets->LoadAssets();

		ProjectionMatrixParams projectionMatrixParams;
		projectionMatrixParams.fieldOfViewY = 45.0f;
		projectionMatrixParams.screenWidth = 800;
		projectionMatrixParams.screenHeight = 600;
		projectionMatrixParams.zNear = 0.1f;
		projectionMatrixParams.zFar = 1800.0f;

		m_scene = std::make_unique<Scene>(*m_assets, screenWidth, screenHeight, m_renderPassManager);
		m_scene->SetProjectionMatrixParams(projectionMatrixParams);
	}

	void Application::Run()
	{
		while (m_isRunning)
		{
			m_isRunning = ( !glfwWindowShouldClose(m_window.GetWindow()) );

			if (Inputs::IsKeyPressed(DeviKey::Key::Escape))
			{
				m_isRunning = false;
			}
			
			double currentTime = glfwGetTime();
			
			m_deltaTime = currentTime - m_lastTime;

			m_lastTime = currentTime;

			//renderer flow (vb->attriblayout->va->bind shader->bind texture->bind uniforms->bind vertexarray->glDrawCall

			m_scene->Update(m_deltaTime);

			m_window.Update();

			m_scene->ClearScene();
		}

		Application::ShutDown();
	}

	void Application::ShutDown()
	{
		m_window.Shutdown();
	}
}