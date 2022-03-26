#include "IndexBuffer.h"
#include <glad/glad.h>
#include <iostream>

namespace Devi
{
	IndexBuffer::IndexBuffer(void* data, size_t dataSize)
		: m_data(data), m_dataSize(dataSize)
	{
		glGenBuffers(1, &m_indexBufferID);
		Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_dataSize, m_data, GL_STATIC_DRAW);
	}

	IndexBuffer::IndexBuffer(std::pair<void*, size_t> indexBufferParams)
		: m_data(indexBufferParams.first), m_dataSize(indexBufferParams.second)
	{
		glGenBuffers(1, &m_indexBufferID);
		Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_dataSize, m_data, GL_STATIC_DRAW);
	}

	size_t IndexBuffer::GetIndexBufferDataSize() const
	{
		return m_dataSize;
	}

	void* IndexBuffer::GetIndexBufferData() const
	{
		return m_data;
	}

	void IndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
	}

	void IndexBuffer::UnBind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
