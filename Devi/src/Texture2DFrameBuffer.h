#pragma once
#include "ITexture.h"
#include "glad/glad.h"

namespace Devi
{
	/**
	* Texture2D class, meant to be attached to a framebuffer. Useful for postprocessing effects
	**/
	class Texture2DFrameBuffer : public ITexture

	{
	public:
		/**
		* Equivalent of glTexParamteri
		**/
		void SetTexParameters(GLenum pname, GLint param);
		
		/**
		* Equivalent of glFramebufferTexture2D. TODO: pass in framebuffer class here for binding.
		**/
		void AttachTextureToFrameBuffer(GLenum attachment, GLenum texTarget);
		void Bind(unsigned int activeTexture = 0) override;
		void UnBind() override;

	private:
		unsigned int m_texture2DFrameBufferID;
	};
}
