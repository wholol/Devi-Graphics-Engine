#pragma once
#include <string.h>
#include "ITexture.h"
#include "Log.h"


namespace Devi
{
	/**
	* CubeMapTexture class. Responsible for loading cubemap textures for skyboxes and binding/unbindiing.
	**/
	class CubeMapTexture : public ITexture
	{
	public:
		CubeMapTexture();
		void Bind(unsigned int activeTexture = 0) override;
		void UnBind() override;

	private:
		unsigned int m_cubeMapTextureID;
	};

}