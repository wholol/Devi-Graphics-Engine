#pragma once
#include "VertexArray.h"
#include "Shader.h"
#include "Math/glm/glm.hpp"
#include <GLAD/glad.h>

namespace Devi
{

	/**
	* Renderer class. Facade for the data(e.g. shader, vertex array, texture) binding flow.
	* Note: //make sure to bind shader first before setting uniforms if adding a new render method. if we set the uniforms and bind it last, the next drawable will be using the shader from the previous drawable.
	*/
	class Renderer
	{
	public:
		static void UpdateViewMatrix(glm::mat4 viewprojectionMatrix);
		static void SetRendererProjectionMatrix(glm::mat4 projectionMatrix);
		
		//render methods.
		static void Render(VertexArray& vertexArray, Shader& shader, glm::mat4 modelMatrix = glm::mat4(1.0), bool ignoreViewMatrixTranslationComponent = false);
		static void RenderWithoutIndexBuffers(int numberOfTriangles,VertexArray& vertexArray, Shader& shader, glm::mat4 modelMatrix = glm::mat4(1.0), bool ignoreViewMatrixTranslationComponent = false);
		static void RenderPatches(int numPatches, VertexArray& vertexArray, Shader& shader, glm::mat4 modelMatrix = glm::mat4(1.0), bool ignoreViewMatrixTranslationComponent = false);
		static void RenderTriangleStrip(int numberofStrips, int numberOfIndicesPerStrip, VertexArray& vertexArray, Shader& shader, glm::mat4 modelMatrix = glm::mat4(1.0), bool ignoreViewMatrixTranslationComponent = false);
		static void RenderQuad(VertexArray& vertexArray, Shader& shader, glm::mat4 modelMatrix = glm::mat4(1.0), bool ignoreViewMatrixTranslationComponent = false);
		
		static void Clear(float r = 0.2f, float g = 0.3f, float b = 0.3f, float a = 1.0f);
		static void EnableDepthTest();
	private:
		static glm::mat4 m_viewMatrix;
		static glm::mat4 m_projectionMatrix;
	};
}