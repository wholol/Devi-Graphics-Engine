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
		static void Clear(float r = 0.2f, float g = 0.3f, float b = 0.3f, float a = 1.0f);
	};
}