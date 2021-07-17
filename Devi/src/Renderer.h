#pragma once
#include "VertexArray.h"
#include "Shader.h"
#include <GLAD/glad.h>

namespace Devi
{
	/**
	* Renderer class. Facade for the data(e.g. shader, vertex array, texture) binding flow.
	**/
	class Renderer
	{
	public:
		static void Render(VertexArray& vertexArray, Shader& shader);
	};
}