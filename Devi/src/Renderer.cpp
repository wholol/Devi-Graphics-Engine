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
