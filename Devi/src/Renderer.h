#pragma once
#include "VertexArray.h"
#include "Shader.h"
#include <GLAD/glad.h>
#include "Math/glm/glm.hpp"

namespace Devi
{
	/**
	* Renderer class. Facade for the data(e.g. shader, vertex array, texture) binding flow.
	*/
	class Renderer
	{
	public:
		static void UpdateViewProjectionMatrix(glm::mat4 viewprojectionMatrix);
		static void Render(VertexArray& vertexArray, Shader& shader, glm::mat4 modelMatrix = glm::mat4(1.0));
		static void Clear(float r = 0.2f, float g = 0.3f, float b = 0.3f, float a = 1.0f);

	private:
		static glm::mat4 m_viewProjectionMatrix;
	};
}