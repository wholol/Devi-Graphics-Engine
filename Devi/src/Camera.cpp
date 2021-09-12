#include "Camera.h"

Devi::Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraTargetPosition)
	:m_cameraPosition(cameraPosition), m_cameraTargetPosition(cameraTargetPosition)
{
	m_cameraLookAtDirection = glm::normalize(m_cameraPosition - m_cameraTargetPosition);
	m_cameraRightVector = glm::cross(GLOBAL_UP_VECTOR, m_cameraLookAtDirection);
	m_cameraUpVector = glm::cross(m_cameraLookAtDirection, m_cameraRightVector);
}

void Devi::Camera::Update(GLFWwindow* window)
{
	move(window);
	rotate(window);
}

glm::mat4 Devi::Camera::getViewMatrix() const
{
	glm::lookAt(m_cameraPosition, m_cameraPosition + m_cameraTargetPosition, m_cameraUpVector);
}

void Devi::Camera::move(GLFWwindow* window)
{
	//forward
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		m_cameraPosition += CAMERA_VELOCITY * m_cameraLookAtDirection;
	}

	//backward
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		m_cameraPosition -= CAMERA_VELOCITY * m_cameraLookAtDirection;
	}

	//move left
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		m_cameraPosition -= CAMERA_VELOCITY * m_cameraRightVector;
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		m_cameraPosition += CAMERA_VELOCITY * m_cameraRightVector;
	}
}

void Devi::Camera::rotate(GLFWwindow* window)
{

}
