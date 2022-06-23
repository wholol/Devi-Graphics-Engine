#include "Camera.h"
#include "Inputs.h"

namespace Devi
{
	Camera::Camera()
	{
		glm::vec3 lookAtVec(1.0);

		lookAtVec.x = cos(glm::radians(m_yawAngle)) * cos(glm::radians(m_pitchAngle));
		lookAtVec.y = sin(glm::radians(m_pitchAngle));
		lookAtVec.z = sin(glm::radians(m_yawAngle)) * cos(glm::radians(m_pitchAngle));
		m_cameraLookAtDirection = glm::normalize(lookAtVec);

		m_cameraRightVector = glm::cross(m_cameraLookAtDirection, GLOBAL_UP_VECTOR);
		m_cameraUpVector = glm::cross(m_cameraRightVector, m_cameraLookAtDirection);
	}

	void Camera::SetPosition(glm::vec3 position)
	{
		m_cameraPosition = position;
	}

	void Camera::Update(double deltaTime)
	{	
		UpdateCameraVectors(deltaTime);
		TranslateCamera(deltaTime);
		//std::cout << m_cameraPosition.y << std::endl;
	}

	const glm::mat4& Camera::GetViewMatrix() const
	{
		return glm::lookAt(m_cameraPosition, m_cameraPosition + m_cameraLookAtDirection, m_cameraUpVector);
	}

	const glm::mat4& Camera::GetWaterReflectionViewMatrix() const
	{
		glm::vec3 waterReflectionCameraPosition = m_cameraPosition;
		waterReflectionCameraPosition.y -= 2.0 * (waterReflectionCameraPosition.y);

		glm::vec3 waterReflectionLookAtDirection = m_cameraLookAtDirection;

		waterReflectionLookAtDirection.y = -waterReflectionLookAtDirection.y;

		return glm::lookAt(waterReflectionCameraPosition, waterReflectionCameraPosition + waterReflectionLookAtDirection, m_cameraUpVector);
	}

	glm::vec3 Camera::GetCameraPosition() const
	{
		return m_cameraPosition;
	}

	void Camera::TranslateCamera(double deltaTime)
	{
		//forward
		if (Inputs::IsKeyPressed(DeviKey::Key::W))
		{
			m_cameraPosition += CAMERA_VELOCITY * static_cast<float>(deltaTime) * m_cameraLookAtDirection;
		}

		if (Inputs::IsKeyPressed(DeviKey::Key::S))
		{
			m_cameraPosition -= CAMERA_VELOCITY * static_cast<float>(deltaTime) * m_cameraLookAtDirection;
		}

		if (Inputs::IsKeyPressed(DeviKey::Key::A))
		{
			m_cameraPosition -= CAMERA_VELOCITY * static_cast<float>(deltaTime) * m_cameraRightVector;
		}

		if (Inputs::IsKeyPressed(DeviKey::Key::D))
		{
			m_cameraPosition += CAMERA_VELOCITY * static_cast<float>(deltaTime) * m_cameraRightVector;
		}

	}

	void Camera::UpdateCameraVectors(double deltaTime)
	{
		auto currentMousePos = Devi::Inputs::GetMousePosInWindow();
		
		if (m_isFirstMouse)
		{
			m_lastMousePos = currentMousePos;
			m_isFirstMouse = false;
		}
		
		auto deltaMousePos = currentMousePos - m_lastMousePos;
		
		m_pitchAngle -= deltaMousePos.y * PITCH_SENSITVITY * deltaTime;
		
		m_yawAngle += deltaMousePos.x * YAW_SENSITIVITY * deltaTime;
		
		if (m_pitchAngle > 89.0)
		{
			m_pitchAngle = 89.0;
		}
		
		if (m_pitchAngle < -89.0)
		{
			m_pitchAngle = -89.0;
		}

		m_cameraLookAtDirection.x = cos(glm::radians(m_yawAngle)) * cos(glm::radians(m_pitchAngle));
		m_cameraLookAtDirection.y = sin(glm::radians(m_pitchAngle));
		m_cameraLookAtDirection.z = sin(glm::radians(m_yawAngle)) * cos(glm::radians(m_pitchAngle));
		m_cameraLookAtDirection = glm::normalize(m_cameraLookAtDirection);

		m_cameraRightVector = glm::cross(m_cameraLookAtDirection, GLOBAL_UP_VECTOR);
		m_cameraUpVector = glm::cross(m_cameraRightVector, m_cameraLookAtDirection);

		m_lastMousePos = currentMousePos;	
	}

}