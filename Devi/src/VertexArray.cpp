#include "VertexArray.h"
#include <glad/glad.h>

Devi::VertexArray::VertexArray(const VertexBuffer & vertexBuffer,std::optional<Devi::IndexBuffer> indexBuffer)
{
	glGenVertexArrays(1, &m_vertexArrayID);
	Bind();
	
	if (indexBuffer.has_value())
	{
		m_hasIndexBuffer = true;
		indexBuffer.value().Bind();
	}

	SetupAndEnableAttribs(vertexBuffer);
}

void Devi::VertexArray::Bind()
{
	glBindVertexArray(m_vertexArrayID);
}

void Devi::VertexArray::UnBind()
{
	glBindVertexArray(0);
}

bool Devi::VertexArray::HasIndexBuffer() const
{
	return m_hasIndexBuffer;
}

Devi::VertexArray::~VertexArray()
{
	UnBind();
}

void Devi::VertexArray::SetupAndEnableAttribs(const VertexBuffer& vertexBuffer)
{
	const auto& vertexBufferLayouts = vertexBuffer.GetVertexBufferLayout();
	unsigned int layoutNumber = 0;
	for (const auto& layout : vertexBufferLayouts)
	{
		glVertexAttribPointer(layoutNumber, layout.numComponents, layout.dataType, layout.isNormalized, vertexBuffer.GetStride(), (void*)(layout.numComponents * sizeof(layout.dataType)));
		glEnableVertexAttribArray(layoutNumber);
		++layoutNumber;
	}
}
