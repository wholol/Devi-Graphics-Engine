#include "glad/glad.h"
#include "Texture2D.h"


Devi::Texture2D::Texture2D(const std::string& textureFilePath, bool generateMipMap)
{
	glGenTextures(1, &m_textureID);
	Bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	int width, height, channels;
	unsigned char *data = stbi_load(textureFilePath.c_str(), &width, &height, &channels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);	
	}
	else
	{
		DEVI_ERROR("texture failed to load for: " + textureFilePath, __FILE__, __LINE__);
	}

	if (generateMipMap)
	{
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	stbi_image_free(data);
}

void Devi::Texture2D::Bind(unsigned int activeTexture)
{
	glActiveTexture(GL_TEXTURE0 + activeTexture);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void Devi::Texture2D::UnBind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
