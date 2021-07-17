#pragma once
#include "ITexture.h"

namespace Devi
{
	/**
	* Texture2D class, meant to be attached to a framebuffer. Useful for postprocessing effects
	**/
	class Texture2DFrameBuffer : public ITexture

	{
	public:
		Texture2DFrameBuffer();
		void Bind() override;
		void UnBind() override;

	private:
		unsigned int m_texture2DFrameBufferID;
	};
}
