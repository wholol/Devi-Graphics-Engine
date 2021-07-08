#include "Application.h"


void Devi::Application::Init(int screenWidth, int screenHeight, const std::string & title)
{
	m_window.Init(screenWidth, screenHeight, title);
}

void Devi::Application::Run()
{
	VertexBuffer triangleVB(Devi::BasicShapes::v_TriangleWithColors, sizeof(Devi::BasicShapes::v_TriangleWithColors));
	VertexArray triangleVA(triangleVB);
	Shader shadertest("Shaders/testshader.vs", "Shaders/testshader.fs");


	while (m_isRunning)
	{
		m_isRunning = !glfwWindowShouldClose(m_window.GetWindow());

		shadertest.Bind();
		triangleVA.Bind();

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
