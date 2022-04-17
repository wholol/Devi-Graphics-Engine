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
		m_modelMatrix = glm::translate(m_modelMatrix, glm::vec3(0.5f, 0.5f, 0.0f));
	}

	void Cube::Draw()
	{
		//TODO: sort out this model matrix. we should and rotate and translate function to move the object.
		m_shader->SetUniform("modelMatrix", m_modelMatrix, UniformDataType::MAT4);
		Renderer::RenderWithoutIndexBuffers(12, *m_vertexArray, *m_shader, m_modelMatrix);
	}
	void Cube::SetShader(std::shared_ptr<Shader> shader)
	{
		m_shader = shader;
	}

	void Cube::SetTextures(std::vector<std::pair<std::shared_ptr<ITexture>, unsigned int>> textures)
	{
	}
}

