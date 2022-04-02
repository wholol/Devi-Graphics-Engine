#include "GPUHeightMap.h"
#include "STBImage/stb_image.h"


namespace Devi
{
	GPUHeightMap::GPUHeightMap(const std::string & heightMapFilePath, const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath,
		const std::string& tessellationControlShaderFilePath,
		const std::string& tessellationEvaluationShaderFilePath,
		const std::string& textureFilePath)
	{
		m_shader.SetShaderFilePath(vertexShaderFilePath, fragmentShaderFilePath, tessellationControlShaderFilePath, tessellationEvaluationShaderFilePath);

		int nChannels;
		unsigned char* data = stbi_load(heightMapFilePath.c_str(), &m_width, &m_height, &nChannels, 0);


		m_grassTexture.CreateTexture2D(textureFilePath.c_str(), GL_RGB, GL_RGB, GL_UNSIGNED_BYTE);
		m_grassTexture.AddTextureParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
		m_grassTexture.AddTextureParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
		
		m_numTiles = 20;
		if (data)
		{
			m_texture2D.CreateTexture2D(heightMapFilePath.c_str(), GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE);
			m_texture2D.AddTextureParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
			m_texture2D.AddTextureParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
			

			//note that we are not using index buffers. this makes sense as we are tessellating the mesh later on.
			for (int x = 0; x < m_numTiles; ++x)
			{
				for (int z = 0; z < m_numTiles; ++z)
				{
					float tileDimensionX = (m_width) / (float)m_numTiles;
					float tileDimensionZ = (m_height) / (float)m_numTiles;

					m_vertices.push_back(-m_width / 2.0f + x * tileDimensionX);
					m_vertices.push_back(0.0f); // v.y
					m_vertices.push_back(-m_height / 2.0f + z * tileDimensionZ); // v.z
					m_vertices.push_back(x / (float)m_numTiles); // u
					m_vertices.push_back(z / (float)m_numTiles); // v


					m_vertices.push_back(-m_width / 2.0f + (x + 1) * tileDimensionX); // v.x
					m_vertices.push_back(0.0f); // v.y
					m_vertices.push_back(-m_height / 2.0f + z * tileDimensionZ); // v.z
					m_vertices.push_back((x + 1) / (float)m_numTiles); // u
					m_vertices.push_back(z / (float)m_numTiles); // v


					m_vertices.push_back(-m_width / 2.0f + m_width * x / (float)m_numTiles); // v.x
					m_vertices.push_back(0.0f); // v.y
					m_vertices.push_back(-m_height / 2.0f + (z + 1) * tileDimensionZ); // v.z
					m_vertices.push_back(x / (float)m_numTiles); // u
					m_vertices.push_back((z + 1) / (float)m_numTiles); // v


					m_vertices.push_back(-m_width / 2.0f + (x + 1) * tileDimensionX); // v.x
					m_vertices.push_back(0.0f); // v.y
					m_vertices.push_back(-m_height / 2.0f + (z + 1) * tileDimensionZ); // v.z
					m_vertices.push_back((x + 1) / (float)m_numTiles); // u
					m_vertices.push_back((z + 1) / (float)m_numTiles); // v

				}
			}

			m_vertexBuffer = std::make_unique<VertexBuffer>(&m_vertices[0], m_vertices.size() * sizeof(float));
			m_vertexBuffer->AddAttribLayout(3);
			m_vertexBuffer->AddAttribLayout(2);
			m_vertexArray = std::make_unique<VertexArray>(*m_vertexBuffer);
		}
		else
		{
			DEVI_ERROR("Failed to load GPU hweight map file.", __FILE__, __LINE__);
		}
	
		stbi_image_free(data);
		m_shader.SetUniform("heightMap", 0, UniformDataType::INT);
		m_shader.SetUniform("grass", 1, UniformDataType::INT);
	}

	void GPUHeightMap::Draw()
	{
		m_shader.Bind();
		
		
		m_texture2D.Bind();
		m_grassTexture.Bind(1);
		glPatchParameteri(GL_PATCH_VERTICES, 4);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		Renderer::RenderPatches(m_numTiles * m_numTiles * 4, *m_vertexArray, m_shader);
	}

}
