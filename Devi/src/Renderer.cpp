#include "Renderer.h"

namespace Devi
{
	glm::mat4 Renderer::m_projectionMatrix{ glm::mat4(1.0) };
	glm::mat4 Renderer::m_viewMatrix{ glm::mat4(1.0) };

	void Renderer::Render(std::shared_ptr<VertexArray> vertexArray)
	{	
		vertexArray->Bind();

		const std::optional<IndexBuffer>& indexBuffer = vertexArray->GetIndexBuffer();

		if (indexBuffer.has_value())
		{
			glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indexBuffer->GetIndexBufferDataSize()), GL_UNSIGNED_INT, 0);
		}
		else
		{
			DEVI_ERROR("Index buffer not set up. Consider Renderer::RenderWithoutIndexBuffers for rendering without index buffer set up.", __FILE__, __LINE__);
		}
	}

	void Renderer::RenderWithoutIndexBuffers(int numberOfTriangles, std::shared_ptr<VertexArray> vertexArray)
	{
		vertexArray->Bind();
		glDrawArrays(GL_TRIANGLES, 0, numberOfTriangles * 3);
	}

	void Renderer::RenderPatches(int numPatches, std::shared_ptr<VertexArray> vertexArray)
	{
		vertexArray->Bind();
		glDrawArrays(GL_PATCHES, 0, numPatches);
	}

	void Renderer::SetRendererViewMatrix(const glm::mat4& viewMatrix)
	{
		m_viewMatrix = viewMatrix;
	}

	void Renderer::SetRendererProjectionMatrix(const glm::mat4& projectionMatrix)
	{
		m_projectionMatrix = projectionMatrix;
	}

	glm::mat4 Renderer::GetRendererViewMatrix()
	{
		return m_viewMatrix;
	}

	glm::mat4 Renderer::GetRendererProjectionMatrix()
	{
		return m_projectionMatrix;
	}

	void Renderer::Clear(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::RenderTriangleStrip(int numberofStrips, int numberOfIndicesPerStrip, std::shared_ptr<VertexArray> vertexArray)
	{
		vertexArray->Bind();

		for (int i = 0; i < numberofStrips; ++i)
		{
			glDrawElements(GL_TRIANGLE_STRIP, numberOfIndicesPerStrip, GL_UNSIGNED_INT,(void*)(i * sizeof(unsigned int) * numberOfIndicesPerStrip));
		}
	}
	void Renderer::RenderQuad(std::shared_ptr<VertexArray> vertexArray)
	{
		vertexArray->Bind();
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}

	void Renderer::EnableDepthTest()
	{
		glEnable(GL_DEPTH_TEST);
	}
}