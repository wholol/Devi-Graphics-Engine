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
	class Cube : public Drawable
	{
		public:
			Cube(const std::string& name);
			void Draw() override;				
	};
}
