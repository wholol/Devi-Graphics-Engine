#pragma once
#include "VertexArray.h"
#include "Shader.h"
#include "Math/glm/glm.hpp"

namespace Devi
{
	/**
	* Renderer class. Facade for the data(e.g. shader, vertex array, texture) binding flow.
	*/
	class Renderer
	{
	public:
		static void UpdateViewMatrix(glm::mat4 viewprojectionMatrix);
		static void SetRendererProjectionMatrix(glm::mat4 projectionMatrix);
		static void Render(VertexArray& vertexArray, Shader& shader, glm::mat4 modelMatrix = glm::mat4(1.0), bool IgnoreViewMatrixTranslationComponent = false);
		static void RenderWithoutIndexBuffers(double numberOfTriangles,VertexArray& vertexArray, Shader& shader, glm::mat4 modelMatrix = glm::mat4(1.0), bool ignoreViewMatrixTranslationComponent = false);
		static void Clear(float r = 0.2f, float g = 0.3f, float b = 0.3f, float a = 1.0f);

	private:
		static glm::mat4 m_viewMatrix;
		static glm::mat4 m_projectionMatrix;
	};
}