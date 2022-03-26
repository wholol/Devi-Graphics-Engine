#pragma once
#include <string>
#include "../src/IDrawable.h"

namespace Devi
{
	/**
	* Height map class. tesselation of the height map done in CPU isntead of tesselation shader.
	*/
	class CPUHeightMap : public IDrawable
	{
	public:
		CPUHeightMap(const std::string& heightMapFilePath, const std::string& vertexShaderFilePath,
			const std::string& fragmentShaderFilePath);
		void Draw() override;

	private:
		int m_width, m_height;
		std::unique_ptr<VertexBuffer> m_vertexBuffer;
		std::unique_ptr<IndexBuffer> m_indexBuffer;
		std::unique_ptr<VertexArray> m_vertexArray;
		std::vector<float> m_vertices;
		std::vector<unsigned int> m_indices;
		Shader m_shader;
		unsigned int m_test = 0;
	};

}