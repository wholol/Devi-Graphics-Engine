#include "VertexBuffer.h"
#include <glad/glad.h>

Devi::VertexBuffer::VertexBuffer(void* data,size_t dataSize)
{
	glGenBuffers(1, &m_vertexBufferID);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
}

void Devi::VertexBuffer::AddAttribLayout(int numberOfComponents, DataTypeForComponents type, bool isNormalized)
{
	m_stride += numberOfComponents;

	if (type == DataTypeForComponents::FLOAT)
	{
		m_layouts.push_back({GL_FLOAT, numberOfComponents, GL_FALSE});
	}

	else if (type == DataTypeForComponents::DOUBLE)
	{
		m_layouts.push_back({GL_DOUBLE, numberOfComponents, GL_FALSE});
	}

	else if (type == DataTypeForComponents::INT)
	{
		m_layouts.push_back({GL_INT, numberOfComponents, GL_FALSE});
	}

	else
	{
		//TODO: implement from std::logic_error
		throw std::runtime_error("Not implemented!");
	}
}

void Devi::VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
}

void Devi::VertexBuffer::UnBind()
{
	glBindBuffer(0, m_vertexBufferID);
}

Devi::VertexBuffer::~VertexBuffer()
{
	UnBind();
}

const std::vector<Devi::VertexBufferLayout>& Devi::VertexBuffer::GetVertexBufferLayout() const
{
	return m_layouts;
}

unsigned int Devi::VertexBuffer::GetStride() const
{
	return m_stride;
}
