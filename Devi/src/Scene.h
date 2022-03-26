#pragma once
#include "Camera.h"
#include "Window.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Math/glm/mat4x4.hpp"
#include "glfw3.h"
#include "Renderer.h"
#include "../Drawables/Cube.h"

namespace Devi
{
	struct ProjectionMatrixParams
	{
		float fieldOfViewY;
		int screenWidth;
		int screenHeight;
		float zNear;
		float zFar;
	};

	using DrawablePtr = std::shared_ptr<IDrawable>;
	/**
	* Scene class. responsible for updating the drawables in the scene.
	*/
	class Scene
	{
	public:

		void SetProjectionMatrixParams(ProjectionMatrixParams projectionMatrixParams);
		void Update(double deltaTime);
		void AddDrawable(DrawablePtr drawable);
		void ClearScene();

	private:
		glm::mat4 m_projectionMatrix{glm::mat4(1.0)};
		Camera m_camera;
		std::vector<DrawablePtr> m_drawables;
	};

}