#pragma once
#include "FrameBuffer.h"
#include "glad/glad.h"
#include "Texture2D.h"
#include "RenderBuffer.h"

namespace Devi
{
	/**
	* Framebuffer with a texture2D and render buffer. Useful for postprocessing effects
	**/
	class Texture2DFrameBuffer

	{
	public:
		Texture2DFrameBuffer(int screenWidth, int screenHeight);

		//note: this binds the framebuffer and texture2D class.
		void Bind();

		void UnBind();

	private:
		unsigned int m_texture2DFrameBufferID;
		int m_screenWidth;
		int m_screenHeight;
		FrameBuffer m_frameBuffer;	//framebuffer that is used to attach to this texture.
		RenderBuffer m_renderBuffer{ m_screenWidth, m_screenHeight };
		Texture2D m_texture2D;

	};
}
