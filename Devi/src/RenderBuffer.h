#pragma once
#include <glad/glad.h>
namespace Devi
{
	class RenderBuffer
	{
	public:
		void CreateRenderBuffer(GLenum internalformat, int height, int width);
		void Bind();
		void UnBind();
		int GetID() const;

	private:
		unsigned int m_renderBufferID;
		int m_width = 0;
		int m_height = 0;
	};
}
