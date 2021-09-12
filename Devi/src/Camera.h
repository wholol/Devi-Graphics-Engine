#pragma once
#include "Math/glm/vec3.hpp"
#include "Math/glm/glm.hpp"
#include "Math/glm/gtc/matrix_transform.hpp"
#include "glfw3.h"

static constexpr glm::vec3 GLOBAL_UP_VECTOR(0.0, 1.0, 0.0);
static constexpr float CAMERA_VELOCITY = 0.05f;

namespace Devi
{

	class Camera
	{

	public:

		Camera(glm::vec3 cameraPosition, glm::vec3 cameraTargetPosition);
		void Update(GLFWwindow* window);
		glm::mat4 getViewMatrix() const;

	private:

		//translates the camera. note: direction vectors should be constant here.
		void move(GLFWwindow* window);
		//rotates the camera around its position. note: direction vectors should be changed here.
		void rotate(GLFWwindow* window);
		glm::vec3 m_cameraPosition = glm::vec3(0.0, 0.0, 0.0);
		glm::vec3 m_cameraTargetPosition = glm::vec3(0.0, 0.0, -1.0);
		
		//camera axis vectors
		glm::vec3 m_cameraLookAtDirection;
		glm::vec3 m_cameraUpVector;
		glm::vec3 m_cameraRightVector;
	};

}