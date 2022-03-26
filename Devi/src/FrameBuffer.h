#pragma once

namespace Devi
{
	class FrameBuffer
	{
	public:
		FrameBuffer();
		void Bind();
		void UnBind();
		~FrameBuffer();
	private:
		unsigned int m_frameBufferID;
		unsigned int m_renderBufferID;
	};

}
