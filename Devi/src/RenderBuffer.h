#pragma once

namespace Devi
{
	class RenderBuffer
	{
	public:
		RenderBuffer(int screenWidth, int screenHeight);
		void Bind();
		void UnBind();

	private:
		unsigned int m_renderBufferID;
	};
}
