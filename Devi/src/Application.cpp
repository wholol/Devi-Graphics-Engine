#include "Application.h"
#include "BasicShapes/BasicShapesVertexData.h"
#include "Math/glm/mat4x4.hpp"

void Devi::Application::Init(int screenWidth, int screenHeight, const std::string & title)
{
	m_window.Init(screenWidth, screenHeight, title);
}

void Devi::Application::Run()
{
	VertexBuffer vb(BasicShapesVertexData::Get(BasicShape::TRIANGLERGB));
	vb.AddAttribLayout(3, DataTypeForComponents::FLOAT);
	vb.AddAttribLayout(3, DataTypeForComponents::FLOAT);
	VertexArray va(vb);

	Shader shadertest("assets/Shaders/testshadervert.vs", "assets/Shaders/testshaderfrag.fs");
	shadertest.SetUniform("u_test", glm::vec4{2,2,2,2}, UniformDataType::VEC4);

	while (m_isRunning)
	{
		m_isRunning = !glfwWindowShouldClose(m_window.GetWindow());
		shadertest.Bind();
		//renderer flow (->bind shader->bind texture->bind uniforms->bind vertexarray->glDrawCall
		va.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);
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
