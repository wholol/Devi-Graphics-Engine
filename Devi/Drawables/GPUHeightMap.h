#pragma once
#include <string>
#include "../src/IDrawable.h"
#include "../src/Texture2D.h"

namespace Devi
{
	// utilizes the tesellation shader to render a height map.
	class GPUHeightMap : public IDrawable
	{
	public:
		GPUHeightMap(const std::string& heightMapFilePath, const std::string& vertexShaderFilePath,
			const std::string& fragmentShaderFilePath,
			const std::string& tessellationControlShaderFilePath,
			const std::string& tessellationEvaluationShaderFilePath,
			const std::string& textureFilePath);
		void Draw() override;

	private:
		int m_width;
		int m_height;
		std::vector<float> m_vertices;
		std::unique_ptr<VertexBuffer> m_vertexBuffer;
		std::unique_ptr<VertexArray> m_vertexArray;
		Shader m_shader;
		Texture2D m_texture2D;
		Texture2D m_grassTexture;
		int m_numTiles = 0;
	};
}