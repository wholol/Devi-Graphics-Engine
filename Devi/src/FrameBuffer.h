#pragma once
#include "Texture2D.h"
#include "RenderBuffer.h"
#include <glad/glad.h>

namespace Devi
{
	class FrameBuffer
	{
	public:
		FrameBuffer(const std::string& name);
		void AttachRenderBufferToFrameBuffer(GLint attachment, RenderBuffer& renderBuffer);
		void AttachTexture2DToFrameBuffer(GLint attachment, Texture2D& texture, int level);
		void SetViewPort(int width, int height);
		void ClearFrameBufferDepth();
		void Bind();
		void UnBind();
		~FrameBuffer();
	private:
		std::string m_name;
		unsigned int m_frameBufferID;
		unsigned int m_renderBufferID;
	};

}
