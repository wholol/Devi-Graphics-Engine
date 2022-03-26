#include "CPUHeightMap.h"
#include "../Dependencies/STBImage/stb_image.h"

namespace
{
	static constexpr float normalize = 255.0f;
	static constexpr float scaleHeight = 50.0f;
}

namespace Devi
{

	CPUHeightMap::CPUHeightMap(const std::string& heightMapFilePath, const std::string& vertexShaderFilePath,
		const std::string& fragmentShaderFilePath)
	{

		int nChannels;
		unsigned char* data = stbi_load(heightMapFilePath.c_str(), &m_width, &m_height, &nChannels, 0);
		//we should end up wtih width * height vertices.
		if (data)
		{
			DEVI_INFO("heightmap data loaded successfully", __FILE__, __LINE__);

			//generate heightmap
			for (int y = 0; y < m_height; ++y)
			{
				for (int x = 0; x < m_width; ++x)
				{
					unsigned char* texel = data + (x + m_width * y) * nChannels;
					unsigned char heightForHeightMap = texel[0];

					m_vertices.emplace_back((-m_height / 2.0f +y));
					m_vertices.emplace_back(((int)heightForHeightMap / normalize) * scaleHeight);
					m_vertices.emplace_back((-m_width / 2.0f + (int)x));
				}
			}
			m_test = m_vertices.size();
			m_vertexBuffer = std::make_unique<VertexBuffer>((void*)&m_vertices[0], m_vertices.size() * sizeof(float));
			m_vertexBuffer->AddAttribLayout(3);

			//generate index buffer
			for (int y = 0; y < m_height - 1; ++y)
			{
				for (int x = 0; x < m_width; ++x)
				{
					//triangle strips in opengl will take the latest index and the last two indexes to form a triangle.
					m_indices.emplace_back(x + m_width * y);
					m_indices.emplace_back( x + m_width * (y + 1));
				}
			}

			m_indexBuffer = std::make_unique<IndexBuffer>(&m_indices[0],m_indices.size() * sizeof(unsigned int));
			m_vertexArray = std::make_unique<VertexArray>(*m_vertexBuffer, *m_indexBuffer);

		}
		else
		{
			DEVI_ERROR("heightmap data failed to load.",__FILE__,__LINE__);
		}

		stbi_image_free(data);

		m_shader.SetShaderFilePath(vertexShaderFilePath, fragmentShaderFilePath);
	}

	void CPUHeightMap::Draw()
	{
		Renderer::RenderTriangleStrip(m_height - 1, m_width * 2, *m_vertexArray, m_shader);
	}

}
