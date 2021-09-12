#include "Renderer.h"

void Devi::Renderer::Render(VertexArray& vertexArray, Shader& shader)
{
	shader.Bind();
	vertexArray.Bind();
	if (vertexArray.HasIndexBuffer())
	{
		//TODO: glDrawElements
	}
	else
	{
		//TODO: glDrawArrays
	}
}

void Devi::Renderer::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}