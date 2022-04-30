#include "glad/glad.h"
#include "Texture2D.h"

namespace Devi
{
	Texture2D::Texture2D(const std::string & name)
		:m_name(name)
	{
	}

	Texture2D::Texture2D(const std::string& name, const std::string& textureFilePath, bool generateMipMap, bool flipImage)
		: m_name(name)
	{
		glGenTextures(1, &m_textureID);
		Bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		stbi_set_flip_vertically_on_load(flipImage);

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

		//NOTE: MipMaps should be generated --AFTER-- loading the texture.
		if (generateMipMap)
		{
			glGenerateMipmap(GL_TEXTURE_2D);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

			//magnification filter does not require mip maps.
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}

		stbi_image_free(data);
	}

	void Texture2D::CreateTexture2D(const std::string& textureFilePath, GLint internalFormat, GLint format, GLenum type, bool generateMipMap, bool flipImage)
	{
		glGenTextures(1, &m_textureID);
		Bind();

		int width, height, channels;

		stbi_set_flip_vertically_on_load(flipImage);

		unsigned char* data = stbi_load(textureFilePath.c_str(), &width, &height, &channels, 0);
		
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, data);
			DEVI_INFO("texture loaded for: " + textureFilePath, __FILE__, __LINE__);
		}
		else
		{
			DEVI_INFO("texture failed to load from: " + textureFilePath, __FILE__, __LINE__);
		}

		stbi_image_free(data);

		//NOTE: MipMaps should be generated --AFTER-- loading the texture.
		if (generateMipMap)
		{
			glGenerateMipmap(GL_TEXTURE_2D);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

			//magnification filter does not require mip maps.
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
	}

	void Texture2D::CreateEmptyTexture2D(GLint internalFormat, int textureHeight, int textureWidth, GLint format, GLenum type)
	{
		glGenTextures(1, &m_textureID);
		Bind();
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, textureWidth, textureHeight, 0, format, type, nullptr);
	}

	void Texture2D::AddTextureParameteri(GLenum textureParam, GLint wrappingMode)
	{
		glTexParameteri(GL_TEXTURE_2D, textureParam, wrappingMode);
	}

	void Texture2D::AddTextureParameterfv(GLenum textureParam,const GLfloat* params)
	{
		glTexParameterfv(GL_TEXTURE_2D, textureParam, params);
	}

	void Texture2D::Bind(unsigned int activeTexture)
	{
		glActiveTexture(GL_TEXTURE0 + activeTexture);
		glBindTexture(GL_TEXTURE_2D, m_textureID);
	}

	void Texture2D::UnBind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	int Texture2D::GetID() const
	{
		return m_textureID;
	}

	std::string Texture2D::GetName() const
	{
		return m_name;
	}

	int Texture2D::GetTextureWidth() const
	{
		return m_textureWidth;
	}

	int Texture2D::GetTextureHeight() const
	{
		return m_textureHeight;
	}
}