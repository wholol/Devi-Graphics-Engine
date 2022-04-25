#include "Cube.h"
#include "../src/Renderer.h"
#include "Math/glm/gtc/matrix_transform.hpp"
#include <glad/glad.h>

namespace Devi
{
	Cube::Cube(const std::string& name)
		:m_name(name)
	{
		m_vertexBuffer.AddAttribLayout(3);
		m_vertexArray = std::make_unique<VertexArray>(m_vertexBuffer);
		//TODFO remove this.
		m_modelMatrix = glm::translate(m_modelMatrix, glm::vec3(0.0f, 200.0f, -200.0f));
		m_modelMatrix = glm::scale(m_modelMatrix, glm::vec3(50.0f, 20.0f, 20.0f));
	}

	void Cube::Draw()
	{
		//m_shader->Bind();
	
		Renderer::RenderWithoutIndexBuffers(12, *m_vertexArray, *m_shader, m_modelMatrix);
	}

	void Cube::SetShader(std::shared_ptr<Shader> shader)
	{
		m_shader = shader;
	}

	void Cube::SetTextures(std::vector<std::pair<std::shared_ptr<ITexture>, unsigned int>> textures)
	{
	}

	std::string Cube::GetName() const
	{
		return m_name;
	}
}

