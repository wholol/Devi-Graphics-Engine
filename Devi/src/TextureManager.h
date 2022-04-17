#pragma once
#include <unordered_map>
#include "ITexture.h"
#include "Texture2D.h"
#include "CubeMapTexture.h"
#include "glad/glad.h"
#include <memory>

namespace Devi
{
	struct TextureParamsSpecification
	{
		GLenum textureParam;
		GLint wrappingMode;
	};

	class TextureManager
	{
	public:

		void AddTexture2D(const std::string& name, 
			const std::string& textureFilePath, 
			const std::vector<TextureParamsSpecification>& textureParamsSpec,
			GLint internalFormat, 
			GLint format, GLenum type, 
			bool generateMipMap = true, 
			bool flipImage = false	
		);
		
		void AddCubeMapTexture(const std::string& name,
			const std::string& rightTextureFilePath, const std::string& leftTextureFilePath,
			const std::string& topTextureFilePath, const std::string& bottomTextureFilePath,
			const std::string& frontTextureFilePath, const std::string& backTextureFilePath);
		
		std::shared_ptr<ITexture> GetTexture(const std::string& name) const;

	private:
		std::unordered_map<std::string, std::shared_ptr<ITexture>> m_textureMap;
	};
}
