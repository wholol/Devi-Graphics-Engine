#include "Cube.h"
#include "../src/Renderer.h"
#include "Math/glm/gtc/matrix_transform.hpp"
#include <glad/glad.h>

namespace Devi
{
	Cube::Cube(const std::string& name)
		:Drawable(name)
	{
		m_vertexBuffer = std::make_shared<VertexBuffer>(BasicShapesVertexData::Get(BasicShape::CUBE));
		m_vertexBuffer->AddAttribLayout(3);
		m_vertexArray = std::make_shared<VertexArray>(*m_vertexBuffer);
		//TODO remove this.
		m_modelMatrix = glm::translate(m_modelMatrix, glm::vec3(0.0f, 200.0f, -200.0f));
		m_modelMatrix = glm::scale(m_modelMatrix, glm::vec3(50.0f, 20.0f, 20.0f));
	}

	void Cube::Draw()
	{
		const int numberOfTrianglesForCube = 12;
		Renderer::RenderWithoutIndexBuffers(numberOfTrianglesForCube, m_vertexArray);
	}
}

