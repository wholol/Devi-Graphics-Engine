#pragma once
#include "Camera.h"
#include "Window.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Math/glm/common.hpp"
#include "glfw3.h"
#include "Renderer.h"
#include "../Drawables/Cube.h"
#include "Texture2D.h"
#include "FrameBuffer.h"
#include "AssetsLoader.h"


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
		Scene(Assets& assets);
		void SetProjectionMatrixParams(ProjectionMatrixParams projectionMatrixParams);
		void Update(double deltaTime);
		void ClearScene();

	private:
		std::vector<DrawablePtr> m_drawables;
		glm::mat4 m_projectionMatrix{glm::mat4(1.0)};
		Camera m_camera;
		
		int m_screenWidth;
		int m_screenHeight;
	};

}