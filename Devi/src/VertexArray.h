#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include <optional>

namespace Devi
{

class VertexArray
{

public:
	VertexArray(VertexBuffer& vertexBuffer, std::optional<IndexBuffer> indexBuffer = {});
	void Bind();
	void UnBind();
	const std::optional<IndexBuffer>& GetIndexBuffer() const;

private:
	unsigned int m_vertexArrayID;
	std::optional<IndexBuffer> m_indexBuffer;
	bool m_hasIndexBuffer = false;

	void SetupAndEnableAttribs(VertexBuffer& vertexBuffer);
};

}