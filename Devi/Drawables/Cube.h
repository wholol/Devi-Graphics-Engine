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
			Cube();
			void Draw() override;		
	private:
			VertexBuffer m_vertexBuffer = VertexBuffer( BasicShapesVertexData::Get(BasicShape::CUBE) );
			std::unique_ptr<VertexArray> m_vertexArray{nullptr};
			Shader m_shader{ "assets/Shaders/cubevs.glsl", "assets/Shaders/cubefs.glsl" };
			glm::mat4 m_modelMatrix{ glm::mat4(1.0) };
	};
}
