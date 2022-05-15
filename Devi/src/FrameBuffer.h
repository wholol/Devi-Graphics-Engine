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
		void AttachRenderBufferToFrameBuffer(GLint attachment, std::shared_ptr<RenderBuffer> renderBuffer);
		void AttachTexture2DToFrameBuffer(GLint attachment, std::shared_ptr<Texture2D> texture, int level);
		void SetViewPort(int width, int height);
		void ClearFrameBufferDepth();
		void Bind();
		void UnBind();
		std::shared_ptr<ITexture> GetTextureAttachment() const;
		std::shared_ptr<RenderBuffer> GetRenderBufferAttachment() const;
		std::string GetName() const;
		~FrameBuffer();
	private:
		std::string m_name;
		unsigned int m_frameBufferID;
		unsigned int m_renderBufferID;
		
		std::shared_ptr<ITexture> m_textureAttachment = nullptr;
		std::shared_ptr<RenderBuffer> m_renderBufferAttachment = nullptr;
	};

}
