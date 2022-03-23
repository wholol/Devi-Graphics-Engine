#include "Camera.h"
#include "Inputs.h"

namespace Devi
{
	Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraTargetPosition)
		:m_cameraPosition(cameraPosition), m_cameraTargetPosition(cameraTargetPosition)
	{
		m_cameraLookAtDirection = glm::normalize(m_cameraPosition - m_cameraTargetPosition);
		m_cameraRightVector = glm::cross(GLOBAL_UP_VECTOR, m_cameraLookAtDirection);
		m_cameraUpVector = glm::cross(m_cameraLookAtDirection, m_cameraRightVector);
	}

	void Camera::Update(double deltaTime)
	{
		translateCamera(deltaTime);
		rotateCamera(deltaTime);
	}

	glm::mat4 Camera::getViewMatrix() const
	{
		return glm::lookAt(m_cameraPosition, m_cameraPosition + m_cameraTargetPosition, m_cameraUpVector);
	}

	void Camera::translateCamera(double deltaTime)
	{
		//forward
		if (Inputs::IsKeyPressed(DeviKey::Key::W))
		{
			m_cameraPosition -= CAMERA_VELOCITY * m_cameraLookAtDirection;
		}

		else if (Inputs::IsKeyPressed(DeviKey::Key::S))
		{
			m_cameraPosition += CAMERA_VELOCITY * m_cameraLookAtDirection;
		}

		else if (Inputs::IsKeyPressed(DeviKey::Key::A))
		{
			m_cameraPosition += CAMERA_VELOCITY * m_cameraRightVector;
		}

		else if (Inputs::IsKeyPressed(DeviKey::Key::D))
		{
			m_cameraPosition -= CAMERA_VELOCITY * m_cameraRightVector;
		}
	}

	void Camera::rotateCamera(double deltaTime)
	{
	}
}