#pragma once

namespace Devi
{
/**
*Index buffer (element buffer object) class. Responsible the storing of EBO and binding/unbinding EBO.
**/
class IndexBuffer
{
	public:
		IndexBuffer() = delete;
		IndexBuffer(void* data, size_t dataSize);
		void Bind();
		void UnBind();
		~IndexBuffer();

	private:
		unsigned int m_indexBufferID;
};

}