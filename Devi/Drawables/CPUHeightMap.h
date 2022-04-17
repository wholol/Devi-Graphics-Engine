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
		CPUHeightMap(const std::string& name, const std::string& heightMapFilePath);
		
		void Draw() override;
		void SetShader(std::shared_ptr<Shader> shader) override;
		void SetTextures(std::vector<std::pair<std::shared_ptr<ITexture>, unsigned int>> textures) override;

	private:
		std::string m_name;
		int m_width, m_height;
		std::unique_ptr<VertexBuffer> m_vertexBuffer;
		std::unique_ptr<IndexBuffer> m_indexBuffer;
		std::unique_ptr<VertexArray> m_vertexArray;
		std::vector<float> m_vertices;
		std::vector<unsigned int> m_indices;
		std::shared_ptr<Shader> m_shader;
		std::vector<std::pair<std::shared_ptr<ITexture>, unsigned int>>  m_textures;
		unsigned int m_test = 0;
	};

}