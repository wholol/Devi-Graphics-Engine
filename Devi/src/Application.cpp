#include "Application.h"
#include "BasicShapes/BasicShapesVertexData.h"
#include "Math/glm/mat4x4.hpp"
#include "Math/glm/vec3.hpp"
#include <string>

namespace Devi
{

	void Application::Init(int screenWidth, int screenHeight, const std::string & title)
	{
		m_window.Init(screenWidth, screenHeight, title);
	}

	void Application::Run()
	{
		VertexBuffer vb(BasicShapesVertexData::Get(BasicShape::RECTANGLERGBTEXCOORDS));
		vb.AddAttribLayout(3);
		vb.AddAttribLayout(3);
		vb.AddAttribLayout(2);
		VertexArray va(vb);

		Shader shadertest("assets/Shaders/testshadervert.vs", "assets/Shaders/testshaderfrag.fs");
		shadertest.SetUniform("texture1", 1, UniformDataType::INT);
		Texture2D tex("assets/Textures/container.png");


		//essentially the update loop is in this while loop.
		while (m_isRunning)
		{
			m_isRunning = !glfwWindowShouldClose(m_window.GetWindow());
			//renderer flow (->bind shader->bind texture->bind uniforms->bind vertexarray->glDrawCall
			//we need texture and shaderManagers for the renderer to know which to bind
			//the renderer flow should be implemented/abstracted to the class Renderer
			//a scene object should have the renderer, scene object calls update on all "things" in the scene
			//partiruclarly the post processing effects, which should be implemented in observer pattern.
			shadertest.Bind();

			tex.Bind();
			va.Bind();
			glDrawArrays(GL_TRIANGLES, 0, 6);
			//update and render here.
			m_window.Update();

			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
		}

		Application::ShutDown();
	}

	void Application::ShutDown()
	{
		m_window.Shutdown();
	}
}