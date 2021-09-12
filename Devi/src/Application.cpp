#include "Application.h"
#include "BasicShapes/BasicShapesVertexData.h"
#include "Math/glm/mat4x4.hpp"
#include "Math/glm/vec3.hpp"

void Devi::Application::Init(int screenWidth, int screenHeight, const std::string & title)
{
	m_window.Init(screenWidth, screenHeight, title);
}

void Devi::Application::Run()
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
		shadertest.Bind();
		//renderer flow (->bind shader->bind texture->bind uniforms->bind vertexarray->glDrawCall
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

void Devi::Application::ShutDown()
{
	m_window.Shutdown();
}
