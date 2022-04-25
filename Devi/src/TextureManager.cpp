#include "TextureManager.h"

namespace Devi
{
	void TextureManager::AddTexture2D(const std::string& name,
		const std::string& textureFilePath,
		const std::vector<TextureParamsSpecification>& textureParamsSpec,
		GLint internalFormat, GLint format, 
		GLenum type, 
		bool generateMipMap, 
		bool flipImage)
	{
		auto findTextureName = m_textureMap.find(name);
		
		if (findTextureName != m_textureMap.end())
		{
			DEVI_ERROR("The texture: " + name + " is not loaded. The name already exists.", __FILE__, __LINE__);
		}
		else
		{
			auto texture2D = std::make_shared<Texture2D>(name);
			texture2D->CreateTexture2D(textureFilePath, internalFormat, format, type, generateMipMap, flipImage);

			for (const auto& textureparam : textureParamsSpec)
			{
				texture2D->AddTextureParameteri(textureparam.textureParam, textureparam.wrappingMode);
			}

			m_textureMap.insert({ name, texture2D });
		}
	}

	std::shared_ptr<ITexture> TextureManager::GetTexture(const std::string & name) const
	{
		auto findTextureName = m_textureMap.find(name);

		if (findTextureName != m_textureMap.end())
		{
			return findTextureName->second;
		}
		else
		{
			DEVI_ERROR("The texture: " + name + " does not exist.", __FILE__, __LINE__);
		}

		return nullptr;
	}

	void TextureManager::AddCubeMapTexture(const std::string& name,
		const std::string& rightTextureFilePath, const std::string& leftTextureFilePath,
		const std::string& topTextureFilePath, const std::string& bottomTextureFilePath,
		const std::string& frontTextureFilePath, const std::string& backTextureFilePath)
	{
		auto findTextureName = m_textureMap.find(name);

		if (findTextureName != m_textureMap.end())
		{
			DEVI_ERROR("The texture: " + name + " is not loaded. The name already exists.", __FILE__, __LINE__);
		}
		else
		{
			auto cubeMapTexture = std::make_shared<CubeMapTexture>(name);

			//Note: do not change the order in which the filepath is added.
			cubeMapTexture->addCubeMapTextures(rightTextureFilePath);
			cubeMapTexture->addCubeMapTextures(leftTextureFilePath);

			cubeMapTexture->addCubeMapTextures(topTextureFilePath);
			cubeMapTexture->addCubeMapTextures(bottomTextureFilePath);

			cubeMapTexture->addCubeMapTextures(frontTextureFilePath);
			cubeMapTexture->addCubeMapTextures(backTextureFilePath);

			cubeMapTexture->GenerateCubeMap();

			m_textureMap.insert({ name, cubeMapTexture });
		}

	}
}

