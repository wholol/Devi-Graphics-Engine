#pragma once
#include <string>
#include "STBImage/stb_image.h"
#include "ITexture.h"
#include "Log.h"

namespace Devi
{
	/**
	* Texture2D class. Responsible for loading 2D textures and binding/unbindiing.
	**/
	class Texture2D : public ITexture
	{
	public:
		Texture2D(const std::string& textureFilePath,bool generateMipMap = true);
		void Bind() override;
		void UnBind() override;

	private:
		unsigned int m_textureID;

	};

}