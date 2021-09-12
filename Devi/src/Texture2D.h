#pragma once
#include <string>
#include "STBImage/stb_image.h"
#include "ITexture.h"
#include "Log.h"

namespace Devi
{
	/**
	* Texture2D class. Responsible for loading 2D textures and binding/unbinding.
	**/
	class Texture2D : public ITexture
	{
	public:
		Texture2D(const std::string& textureFilePath,bool generateMipMap = true, bool flipImage = true);
		void Bind(unsigned int activeTexture = 0) override;
		void UnBind() override;

	private:
		unsigned int m_textureID;

	};

}