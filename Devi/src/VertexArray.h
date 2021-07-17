#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include <optional>

namespace Devi
{

class VertexArray
{

public:
	VertexArray(VertexBuffer& vertexBuffer, std::optional<Devi::IndexBuffer> indexBuffer = {});
	void Bind();
	void UnBind();
	bool HasIndexBuffer() const;

private:
	unsigned int m_vertexArrayID;
	bool m_hasIndexBuffer = false;
	void SetupAndEnableAttribs(VertexBuffer& vertexBuffer);
};

}