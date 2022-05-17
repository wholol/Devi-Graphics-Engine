#include "SkyBox.h"

namespace Devi
{
	SkyBox::SkyBox(const std::string& name)
		:Drawable(name)
	{
		m_vertexBuffer = std::make_shared<VertexBuffer>(BasicShapesVertexData::Get(BasicShape::CUBE));
		m_vertexBuffer->AddAttribLayout(3);
		m_vertexArray = std::make_shared<VertexArray>(*m_vertexBuffer);
	}

	void SkyBox::Draw()
	{
		const int numTriangles = 12;
		glDepthFunc(GL_LEQUAL);
		Renderer::RenderWithoutIndexBuffers(numTriangles, m_vertexArray);
		glDepthFunc(GL_LESS);
	}
}

