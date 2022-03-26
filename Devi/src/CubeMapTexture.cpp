#include "CubeMapTexture.h"
#include <glad/glad.h>
#include "../Dependencies/STBImage/stb_image.h"

namespace Devi 
{
	CubeMapTexture::CubeMapTexture()
	{
		glGenTextures(1, &m_cubeMapTextureID);
	}

	void CubeMapTexture::addCubeMapTextures(const std::string& textureFilePath)
	{
		m_cubeMapTextureFilePaths.push_back(textureFilePath);
	}

	void CubeMapTexture::GenerateCubeMap()
	{
		if (m_cubeMapTextureFilePaths.size() != m_numberOfFaces)
		{
			DEVI_ERROR("Detected that cubeMap texture filepaths loaded are not equal to 6.", __FILE__, __LINE__);
			return;
		}

		Bind();

		for (int i = 0; i < m_numberOfFaces; ++i)
		{
			int width, height, channels;
			unsigned char* data = stbi_load(m_cubeMapTextureFilePaths[i].c_str(), &width, &height, &channels, 0);

			if (data)
			{
				DEVI_INFO("Cubemap loaded successfully",__FILE__, __LINE__);
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, (void*)data);
			}
			else
			{
				DEVI_ERROR("loading cubemap has failed at: " + m_cubeMapTextureFilePaths[i], __FILE__, __LINE__);
			}

			stbi_image_free(data);
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	}

	void CubeMapTexture::Bind(unsigned int activeTexture)
	{
		glActiveTexture(GL_TEXTURE0 + activeTexture);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubeMapTextureID);
	}

	void CubeMapTexture::UnBind()
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

}