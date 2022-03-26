#include "Renderer.h"

namespace Devi
{
	glm::mat4 Renderer::m_projectionMatrix{ glm::mat4(1.0) };
	glm::mat4 Renderer::m_viewMatrix{ glm::mat4(1.0) };

	void Renderer::Render(VertexArray& vertexArray, Shader& shader, glm::mat4 modelMatrix, bool ignoreViewMatrixTranslationComponent)
	{
		shader.Bind();
		shader.SetUniform("modelMatrix", modelMatrix, UniformDataType::MAT4);
		
		if (ignoreViewMatrixTranslationComponent)
		{
			m_viewMatrix = glm::mat4(glm::mat3(m_viewMatrix));
		}

		shader.SetUniform("viewMatrix", m_viewMatrix, UniformDataType::MAT4);
		shader.SetUniform("projectionMatrix", m_projectionMatrix, UniformDataType::MAT4);
		
		vertexArray.Bind();

		const std::optional<IndexBuffer>& indexBuffer = vertexArray.GetIndexBuffer();

		if (indexBuffer.has_value())
		{
			glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indexBuffer->GetIndexBufferDataSize()), GL_UNSIGNED_INT, 0);
		}
		else
		{
			DEVI_ERROR("Index buffer not set up. Consider Renderer::RenderWithoutIndexBuffers for rendering without index buffer set up.", __FILE__, __LINE__);
		}
	}

	void Renderer::RenderWithoutIndexBuffers(int numberOfTriangles, VertexArray & vertexArray, Shader & shader, glm::mat4 modelMatrix, bool ignoreViewMatrixTranslationComponent)
	{
		
		shader.Bind();
		shader.SetUniform("modelMatrix", modelMatrix, UniformDataType::MAT4);

		if (ignoreViewMatrixTranslationComponent)
		{
			m_viewMatrix = glm::mat4(glm::mat3(m_viewMatrix));
		}

		shader.SetUniform("viewMatrix", m_viewMatrix, UniformDataType::MAT4);
		shader.SetUniform("projectionMatrix", m_projectionMatrix, UniformDataType::MAT4);

		vertexArray.Bind();

		glDrawArrays(GL_TRIANGLES, 0, numberOfTriangles * 3);
	}


	void Renderer::UpdateViewMatrix(glm::mat4 viewMatrix)
	{
		m_viewMatrix = viewMatrix;
	}

	void Renderer::SetRendererProjectionMatrix(glm::mat4 projectionMatrix)
	{
		m_projectionMatrix = projectionMatrix;
	}

	void Renderer::Clear(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::RenderTriangleStrip(int numberofStrips, int numberOfIndicesPerStrip, VertexArray& vertexArray, Shader& shader, glm::mat4 modelMatrix, bool ignoreViewMatrixTranslationComponent)
	{
		shader.Bind();
		shader.SetUniform("modelMatrix", modelMatrix, UniformDataType::MAT4);

		if (ignoreViewMatrixTranslationComponent)
		{
			m_viewMatrix = glm::mat4(glm::mat3(m_viewMatrix));
		}

		shader.SetUniform("viewMatrix", m_viewMatrix, UniformDataType::MAT4);
		shader.SetUniform("projectionMatrix", m_projectionMatrix, UniformDataType::MAT4);
		
		vertexArray.Bind();

		for (int i = 0; i < numberofStrips; ++i)
		{
			glDrawElements(GL_TRIANGLE_STRIP, numberOfIndicesPerStrip, GL_UNSIGNED_INT,(void*)(i * sizeof(unsigned int) * numberOfIndicesPerStrip));
		}
	}
	void Renderer::EnableDepthTest()
	{
		glEnable(GL_DEPTH_TEST);
	}
}