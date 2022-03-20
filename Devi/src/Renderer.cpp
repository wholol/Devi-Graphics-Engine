#include "Renderer.h"

namespace Devi
{
	void Renderer::Render(VertexArray& vertexArray, Shader& shader, glm::mat4 modelMatrix)
	{
		shader.Bind();
		vertexArray.Bind();

		const std::optional<IndexBuffer>& indexBuffer = vertexArray.GetIndexBuffer();

		if (indexBuffer.has_value())
		{
			glDrawElements(GL_TRIANGLES, indexBuffer->GetIndexBufferDataSize(), GL_UNSIGNED_INT,indexBuffer->GetIndexBufferData());
		}
		else
		{
			//TODO: we need to calculate the number of vertices manually fro mthe vertexbuffer data to solve this issue. currently hard coded to render a cuve (36 vertices).
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}

	void Renderer::UpdateViewProjectionMatrix(glm::mat4 viewProjectionMatrix)
	{
		m_viewProjectionMatrix = viewProjectionMatrix;
	}

	void Renderer::Clear(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}