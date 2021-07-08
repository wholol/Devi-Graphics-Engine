#include "IndexBuffer.h"
#include <glad/glad.h>

Devi::IndexBuffer::IndexBuffer(void* data, size_t dataSize)
{
	glGenBuffers(1, &m_indexBufferID);
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
}

void Devi::IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
}

void Devi::IndexBuffer::UnBind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Devi::IndexBuffer::~IndexBuffer()
{
	UnBind();
}
