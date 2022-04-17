#pragma once
#include <string>
#include "../src/IDrawable.h"
#include "../src/Texture2D.h"
#include "../Light/Light.h"
#include <algorithm>

namespace Devi
{
	// utilizes the tesellation shader to render a height map.
	class GPUHeightMap : public IDrawable
	{
	public:
		GPUHeightMap(const std::string& name, const std::string& heightMapFilePath);
		
		void Draw() override;
		void SetShader(std::shared_ptr<Shader> shader) override;
		void SetTextures(std::vector<std::pair<std::shared_ptr<ITexture>, unsigned int>> textures) override;

	private:
		std::string m_name;
		int m_width;
		int m_height;
		std::vector<float> m_vertices;
		std::unique_ptr<VertexBuffer> m_vertexBuffer;
		std::unique_ptr<VertexArray> m_vertexArray;
		
		std::shared_ptr<Shader> m_shader;
		std::vector<std::pair<std::shared_ptr<ITexture>, unsigned int>>  m_textures;
		
		std::shared_ptr<Texture2D> m_texture2D;
		int m_numTiles = 0;
	};
}