#include "VertexBuffer.h"
#include <glad/glad.h>

namespace Devi
{

	VertexBuffer::VertexBuffer(void* data, unsigned long long int dataSize)
	{
		glGenBuffers(1, &m_vertexBufferID);
		Bind();
		glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
	}

	VertexBuffer::VertexBuffer(std::pair<void*, size_t> VertexBufferParams)
	{
		glGenBuffers(1, &m_vertexBufferID);
		Bind();
		glBufferData(GL_ARRAY_BUFFER, VertexBufferParams.second, VertexBufferParams.first, GL_STATIC_DRAW);
	}

	void VertexBuffer::AddAttribLayout(int numberOfComponentsForAttrib, DataTypeForComponents type, bool isNormalized)
	{
		m_stride += numberOfComponentsForAttrib;

		try
		{

			if (type == DataTypeForComponents::FLOAT)
			{
				m_layouts.push_back({ GL_FLOAT, numberOfComponentsForAttrib, GL_FALSE });
			}

			else if (type == DataTypeForComponents::DOUBLE)
			{
				m_layouts.push_back({ GL_DOUBLE, numberOfComponentsForAttrib, GL_FALSE });
			}

			else if (type == DataTypeForComponents::INT)
			{
				m_layouts.push_back({ GL_INT, numberOfComponentsForAttrib, GL_FALSE });
			}

			else
			{
				throw Exception::NotImplementedException("attrib layout type not implemented.", __FILE__, __LINE__);
			}
		}

		catch (std::exception& e)
		{
			DEVI_ERROR(e.what(), __FILE__, __LINE__);
		}

	}

	void VertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
	}

	void VertexBuffer::UnBind()
	{
		glBindBuffer(0, m_vertexBufferID);
	}

	const std::vector<Devi::VertexBufferLayout>& Devi::VertexBuffer::GetVertexBufferLayout() const
	{
		return m_layouts;
	}

	unsigned int VertexBuffer::GetStride() const
	{
		return m_stride;
	}
}