#include "WaterQuad.h"
#include "IDrawable.h"

namespace Devi
{

	WaterQuad::WaterQuad(const std::string& name, int width, int height, int numTiles)
		:Drawable(name),
		m_width(width),
		m_height(height)
	{
		for (int z = 0; z < m_height; ++z)
		{
			for (int x = 0; x < m_width; ++x)
			{
				m_vertices.push_back(-m_width/2.0f  + x);
				m_vertices.push_back(0);
				m_vertices.push_back(-m_height/ 2.0f + z);
			}
		}

		for (int z = 0; z < m_height - 1; ++z)
		{
			for (int x = 0; x < m_width; ++x)
			{
				m_indices.push_back(x + m_width * z);
				m_indices.push_back(x + m_width * (z + 1));
			}
		}

		m_vertexBuffer = std::make_shared<VertexBuffer>(&(m_vertices[0]),sizeof(float) * m_vertices.size());
		m_indexBuffer = std::make_shared<IndexBuffer>(&(m_indices[0]), sizeof(float) * m_indices.size());
		m_vertexArray = std::make_shared<VertexArray>(*m_vertexBuffer, *m_indexBuffer);
	}

	void WaterQuad::Draw()
	{
		Renderer::RenderTriangleStrip(m_height - 1, m_width * 2, m_vertexArray);
	}

}

