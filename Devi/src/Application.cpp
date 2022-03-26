#include "Application.h"
#include "BasicShapes/BasicShapesVertexData.h"
#include "Math/glm/mat4x4.hpp"
#include "Math/glm/vec3.hpp"
#include <string>
#include "Camera.h"

#include "SkyBox.h"
#include "CPUHeightMap.h"

namespace Devi
{
	Application::Application(int screenWidth, int screenHeight, const std::string& title)
	{
		m_window.Init(screenWidth, screenHeight, title);	//IMPORTANT. THIS FUNCTION SHOULD BE COMPLETED BEFORE ANY GLAD CODE SHOULD BE RUN, OR THE APP CRASHES.
		m_screenWidth = screenWidth;
		m_screenHeight = screenHeight;
		Inputs::Init(&m_window);
		ProjectionMatrixParams projectionMatrixParams;
		projectionMatrixParams.fieldOfViewY = 90.0f;
		projectionMatrixParams.screenWidth = 800;
		projectionMatrixParams.screenHeight = 600;
		projectionMatrixParams.zNear = 0.1f;
		projectionMatrixParams.zFar = 100000.0f;

		m_scene = std::make_unique<Scene>();
		m_scene->SetProjectionMatrixParams(projectionMatrixParams);

		m_scene->AddDrawable(std::move(std::make_unique<CPUHeightMap>(
			"assets/Textures/iceland_heightmap.png",
			"assets/Shaders/CPUHeightmap_vs.glsl", "assets/Shaders/CPUHeightmap_fs.glsl"))
		);

		m_scene->AddDrawable(std::move(std::make_unique<SkyBox>(
			"assets/Textures/Daylight Box_Right.bmp", "assets/Textures/Daylight Box_Left.bmp",
			"assets/Textures/Daylight Box_Top.bmp", "assets/Textures/Daylight Box_Bottom.bmp",
			"assets/Textures/Daylight Box_Front.bmp", "assets/Textures/Daylight Box_Back.bmp",
			"assets/Shaders/skybox_vs.glsl", "assets/Shaders/skybox_fs.glsl")));
	}

	void Application::Run()
	{
		while (m_isRunning)
		{
			m_isRunning = !glfwWindowShouldClose(m_window.GetWindow());
			
			double currentTime = glfwGetTime();
			
			deltaTime = currentTime - lastTime;

			currentTime = lastTime;

			//renderer flow (vb->attriblayout->va->bind shader->bind texture->bind uniforms->bind vertexarray->glDrawCall
			//we need texture and shaderManagers for the renderer to know which to bind

			m_scene->Update(deltaTime);

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