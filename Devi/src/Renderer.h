#pragma once
#include "VertexArray.h"
#include "Shader.h"
#include "Math/glm/glm.hpp"
#include <GLAD/glad.h>

namespace Devi
{

	/**
	* Renderer class. Binds VA and performs gl draw calls
	* Note: //make sure to bind shader first before setting uniforms if adding a new render method. if we set the uniforms and bind it last, the next drawable will be using the shader from the previous drawable.
	*/
	class Renderer
	{
	public:
		static void SetRendererViewMatrix(const glm::mat4& viewMatrix);
		static void SetWaterReflectionViewMatrix(const glm::mat4& viewMatrix);
		static void SetRendererProjectionMatrix(const glm::mat4& projectionMatrix);
		static glm::mat4 GetRendererViewMatrix();
		static glm::mat4 GetRendererProjectionMatrix();
		static glm::mat4 GetRendererWaterReflectionViewMatrix();
		
		//render methods.
		static void Render(std::shared_ptr<VertexArray> vertexArray);
		static void RenderWithoutIndexBuffers(int numberOfTriangles, std::shared_ptr<VertexArray> vertexArray);
		static void RenderPatches(int numPatches, std::shared_ptr<VertexArray> vertexArray);
		static void RenderTriangleStrip(int numberofStrips, int numberOfIndicesPerStrip, std::shared_ptr<VertexArray> vertexArray);
		static void RenderQuad(std::shared_ptr<VertexArray> vertexArray);
		
		static void Clear(float r = 0.2f, float g = 0.3f, float b = 0.3f, float a = 1.0f);
		static void EnableDepthTest();
	private:
		static glm::mat4 m_viewMatrix;
		static glm::mat4 m_waterReflectionViewMatrix;
		static glm::mat4 m_projectionMatrix;
	};
}