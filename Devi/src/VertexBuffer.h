#pragma once
#include <vector>

namespace Devi
{
	struct VertexBufferLayout
	{
		unsigned int dataType;
		int numComponents;
		bool isNormalized;
	};

	/**
	* Possible data types for components (e.g. color, position). add new data type here if needed.
	**/
	enum class DataTypeForComponents
	{
		FLOAT,
		DOUBLE,
		INT 
	};

	/**
	* This class is responsible for binding vertex buffer and the vertex attrib layout data requried for a vertex buffer.
	**/
	class VertexBuffer
	{

	public:
		VertexBuffer() = delete;
		VertexBuffer(void* data, size_t dataSize);
		void Bind();
		void UnBind();
		void AddAttribLayout(int numberOfComponents, DataTypeForComponents type, bool isNormalized = false);
		const std::vector<VertexBufferLayout>& GetVertexBufferLayout() const;
		unsigned int GetStride() const;
		~VertexBuffer();

	private:
		unsigned int m_vertexBufferID;
		unsigned int m_stride = 0;
		std::vector<VertexBufferLayout> m_layouts;
	};
}
