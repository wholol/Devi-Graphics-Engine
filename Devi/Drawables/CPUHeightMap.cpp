#include "CPUHeightMap.h"
#include "../Dependencies/STBImage/stb_image.h"

namespace
{
	static constexpr float normalize = 255.0f;
	static constexpr float scaleHeight = 100.0f;
}

namespace Devi
{

	CPUHeightMap::CPUHeightMap(const std::string& name, const std::string& heightMapFilePath)
		:m_name(name)
	{

		int nChannels;
		unsigned char* data = stbi_load(heightMapFilePath.c_str(), &m_width, &m_height, &nChannels, 0);
		//we should end up wtih width * height vertices.
		if (data)
		{
			DEVI_INFO("heightmap data loaded successfully", __FILE__, __LINE__);

			//generate heightmap
			//note that we are not loading the pixel edges, only the y value is useful to us in the pixel, which is translated into a vertex point.
			for (int z = 0; z < m_height; ++z)
			{
				for (int x = 0; x < m_width; ++x)
				{
					unsigned char* texel = data + (x + m_width * z) * nChannels;
					unsigned char heightForHeightMap = *texel;
					
					m_vertices.emplace_back((-m_width / 2.0f + (int)x));	//x
					m_vertices.emplace_back(((int)heightForHeightMap / normalize) * scaleHeight);	//y
					m_vertices.emplace_back((-m_height / 2.0f + z));	//z
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

	}

	void CPUHeightMap::Draw()
	{
		Renderer::RenderTriangleStrip(m_height - 1, m_width * 2, *m_vertexArray, *m_shader);
	}

	void CPUHeightMap::SetShader(std::shared_ptr<Shader> shader)
	{
		m_shader = shader;
	}

	void CPUHeightMap::SetTextures(std::vector<std::pair<std::shared_ptr<ITexture>, unsigned int>> textures)
	{
	}

	std::string CPUHeightMap::GetName() const
	{
		return m_name;
	}

}
