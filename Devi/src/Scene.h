#pragma once
#include "Camera.h"
#include "Window.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Math/glm/mat4x4.hpp"
#include <glfw3.h>
#include "Renderer.h"
namespace Devi
{
	struct ProjectionMatrixParams
	{
		float FieldOfViewY;
		int screenWidth;
		int screenHeight;
		float zNear;
		float zFar;
	};

	/**
	* Scene class. responsible for rendering objects on the screen.
	*/
	class Scene
	{
	public:
		void SetProjectionMatrixParams(ProjectionMatrixParams projectionMatrixParams);
		void Update(GLFWwindow* window, double deltaTime);
	private:
		glm::mat4 m_projectionMatrix;
		Camera m_camera;
	};

}