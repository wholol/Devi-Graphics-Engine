#pragma once
#include <utility>

namespace Devi
{
	/**
	* Index buffer (element buffer object) class. Responsible the storing of EBO and binding/unbinding EBO.
	*/
	class IndexBuffer
	{
		public:
			IndexBuffer() = delete;
			IndexBuffer(void* data, size_t dataSize);
			IndexBuffer(std::pair<void*, size_t> IndexBufferParams);
			size_t GetIndexBufferDataSize() const;
			void* GetIndexBufferData() const;
			void Bind();
			void UnBind();
	
		private:
			unsigned int m_indexBufferID;
			void* m_data;
			size_t m_dataSize;
	};

}