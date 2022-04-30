#pragma once
#include <string>
#include "STBImage/stb_image.h"
#include <optional>
#include "ITexture.h"
#include "Log.h"
#include <glad/glad.h>

namespace Devi
{
	/**
	* Texture2D class. Responsible for loading 2D textures and binding/unbinding.
	**/
	class Texture2D : public ITexture
	{
	public:
		Texture2D(const std::string& name);	//for empty textures
		Texture2D(const std::string& name, const std::string& textureFilePath,bool generateMipMap = true, bool flipImage = true);
		void CreateTexture2D(const std::string& textureFilePath, GLint internalFormat, GLint format, GLenum type, bool generateMipMap = true, bool flipImage = false);
		//creates an empty texture with no data.
		void CreateEmptyTexture2D(GLint internalFormat, int textureHeight, int textureWidth, GLint format, GLenum type);
		void AddTextureParameteri(GLenum textureParam, GLint wrappingMode);
		void AddTextureParameterfv(GLenum textureParam, const GLfloat* params);
		void Bind(unsigned int activeTexture = 0) override;
		void UnBind() override;
		int GetID() const;
		std::string GetName() const override;
		int GetTextureWidth() const;
		int GetTextureHeight() const;

	private:
		unsigned int m_textureID;
		std::string m_name;
		int m_textureWidth;
		int m_textureHeight;
	};

}