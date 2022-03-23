#pragma once
#include <string.h>
#include "ITexture.h"
#include "Log.h"
#include <vector>
namespace Devi
{
	/**
	* CubeMapTexture class. Responsible for loading cubemap textures for skyboxes and binding/unbindiing.
	**/
	class CubeMapTexture : public ITexture
	{
	public:

		CubeMapTexture();
		void addCubeMapTextures(const std::string& textureFilePath);
		void GenerateCubeMap();
		void Bind(unsigned int activeTexture = 0) override;
		void UnBind() override;

	private:
		unsigned int m_cubeMapTextureID;
		std::vector<std::string> m_cubeMapTextureFilePaths;
		static constexpr unsigned int m_numberOfFaces = 6;
	};

}