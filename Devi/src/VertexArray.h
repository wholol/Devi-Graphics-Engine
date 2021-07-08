#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include <optional>

namespace Devi
{

class VertexArray
{

public:

	VertexArray(const VertexBuffer& vertexBuffer,std::optional<Devi::IndexBuffer> indexBuffer = {});
	void Bind();
	void UnBind();
	bool HasIndexBuffer() const;
	~VertexArray();

private:
	unsigned int m_vertexArrayID;
	bool m_hasIndexBuffer = false;
	void SetupAndEnableAttribs(const VertexBuffer& vertexBuffer);
};

}