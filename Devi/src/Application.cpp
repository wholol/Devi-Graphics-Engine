#include "Application.h"
#include "BasicShapes/BasicShapesVertexData.h"
#include "Math/glm/mat4x4.hpp"
#include "Math/glm/vec3.hpp"
#include <string>
#include "Camera.h"

namespace Devi
{

	void Application::Init(int screenWidth, int screenHeight, const std::string& title)
	{
		m_window.Init(screenWidth, screenHeight, title);
		m_screenWidth = screenWidth;
		m_screenHeight = screenHeight;
	}

	void Application::Run()
	{
		VertexBuffer vb(BasicShapesVertexData::Get(BasicShape::CUBE));
		vb.AddAttribLayout(3);
		//vb.AddAttribLayout(3);
		//vb.AddAttribLayout(2);
		VertexArray va(vb);

		glm::mat4 modelTransform = glm::mat4(1.0f);
		auto newModel = glm::translate(modelTransform, glm::vec3(0.5f, -0.5f, -40.0f));

		float aspect = static_cast<float>(m_screenWidth) / static_cast<float>(m_screenHeight);

		const glm::mat4 projectionMatrix = glm::perspective(glm::radians(10.0f), aspect, 0.1f, 100.0f);
		
		Shader shadertest("assets/Shaders/cubevs.glsl", "assets/Shaders/cubefs.glsl");
		//shadertest.SetUniform("texture1", 1, UniformDataType::INT);

		Texture2D tex("assets/Textures/container.png");

		//essentially the update loop is in this while loop.
		while (m_isRunning)
		{
			m_isRunning = !glfwWindowShouldClose(m_window.GetWindow());
			
			double currentTime = glfwGetTime();
			
			double deltaTime = currentTime - lastTime;

			currentTime = lastTime;

			const auto& viewMatrix = m_camera.getViewMatrix();

			shadertest.SetUniform("modelMatrix", newModel, UniformDataType::MAT4);
			shadertest.SetUniform("projectionMatrix", projectionMatrix, UniformDataType::MAT4);
			shadertest.SetUniform("viewMatrix", viewMatrix, UniformDataType::MAT4);
			//renderer flow (->bind shader->bind texture->bind uniforms->bind vertexarray->glDrawCall
			//we need texture and shaderManagers for the renderer to know which to bind
			//the renderer flow should be implemented/abstracted to the class Renderer
			//a scene object should have the renderer, scene object calls update on all "things" in the scene
			//partiruclarly the post processing effects, which should be implemented in observer pattern.
			shadertest.Bind();

			m_camera.Update(m_window.GetWindow(), deltaTime);

			va.Bind();
			glDrawArrays(GL_TRIANGLES, 0, 36);
			//update and render here.
			m_window.Update();

			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		Application::ShutDown();
	}

	void Application::ShutDown()
	{
		m_window.Shutdown();
	}
}