#pragma once
#include "../src/IDrawable.h"
#include "../assets/BasicShapes/BasicShapesVertexData.h"
#include "../src/Shader.h"
#include "Math/glm/glm.hpp"

namespace Devi
{
	/**
	* A class that contains vertex array and vertex buffer of a cube.
	*/
	class Cube : public IDrawable
	{
		public:
			Cube(const std::string& name);
			void Draw() override;		
			void SetShader(std::shared_ptr<Shader> shader) override;
			void SetTextures(std::vector<std::pair<std::shared_ptr<ITexture>, unsigned int>> textures) override;
			std::string GetName() const override;

	private:
			std::string m_name;
			VertexBuffer m_vertexBuffer = VertexBuffer( BasicShapesVertexData::Get(BasicShape::CUBE) );
			std::unique_ptr<VertexArray> m_vertexArray{nullptr};
			std::shared_ptr<Shader> m_shader;
			glm::mat4 m_modelMatrix{ glm::mat4(1.0) };
	};
}
