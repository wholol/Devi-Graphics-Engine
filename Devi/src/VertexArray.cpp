#include "VertexArray.h"
#include <glad/glad.h>

namespace Devi
{
	VertexArray::VertexArray(VertexBuffer& vertexBuffer, std::optional<Devi::IndexBuffer> indexBuffer)
		: m_indexBuffer(indexBuffer)
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

	void VertexArray::Bind()
	{
		glBindVertexArray(m_vertexArrayID);
	}

	void VertexArray::UnBind()
	{
		glBindVertexArray(0);
	}

	const std::optional<IndexBuffer>& VertexArray::GetIndexBuffer() const
	{
		return m_indexBuffer;
	}

	void VertexArray::SetupAndEnableAttribs(VertexBuffer& vertexBuffer)
	{
		const auto& vertexBufferLayouts = vertexBuffer.GetVertexBufferLayout();
		unsigned int layoutNumber = 0;
		unsigned int vertexAttribOffset = 0;
		for (const auto& layout : vertexBufferLayouts)
		{
			int numComponents = layout.numComponentsForAttrib;
			bool isNormalized = layout.isNormalized;
			unsigned int dataType = layout.dataType;
			int stride = vertexBuffer.GetStride() * sizeof(dataType);

			glVertexAttribPointer(layoutNumber, numComponents, dataType, isNormalized, stride, (void*)(vertexAttribOffset * sizeof(dataType)));
			glEnableVertexAttribArray(layoutNumber);

			vertexAttribOffset += numComponents;
			++layoutNumber;
		}
	}
}