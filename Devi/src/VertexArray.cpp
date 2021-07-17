#include "VertexArray.h"
#include <glad/glad.h>

Devi::VertexArray::VertexArray(VertexBuffer& vertexBuffer, std::optional<Devi::IndexBuffer> indexBuffer)
{
	glGenVertexArrays(1, &m_vertexArrayID);
	Bind();
	vertexBuffer.Bind();

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

void Devi::VertexArray::SetupAndEnableAttribs(VertexBuffer& vertexBuffer)
{
	const auto& vertexBufferLayouts = vertexBuffer.GetVertexBufferLayout();
	unsigned int layoutNumber = 0;
	unsigned int vertexAttribOffset = 0;
	for (const auto& layout : vertexBufferLayouts)
	{
		int numComponents = layout.numComponents;
		bool isNormalized = layout.isNormalized;
		unsigned int dataType = layout.dataType;
		int stride = vertexBuffer.GetStride() * sizeof(dataType);

		glVertexAttribPointer(layoutNumber, numComponents, dataType, isNormalized, stride, (void*)(vertexAttribOffset * sizeof(dataType)));
		glEnableVertexAttribArray(layoutNumber);
		
		vertexAttribOffset += numComponents;
		++layoutNumber;
	}
}
