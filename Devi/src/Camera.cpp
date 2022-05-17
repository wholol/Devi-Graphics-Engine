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

	void Camera::SetPosition(glm::vec3 cameraPosition)
	{
		m_cameraPosition = cameraPosition;
	}

	void Camera::Update(double deltaTime)
	{	
		UpdateCameraVectors(deltaTime);
		TranslateCamera(deltaTime);
	}

	const glm::mat4& Camera::GetViewMatrix() const
	{
		return glm::lookAt(m_cameraPosition, m_cameraPosition + m_cameraLookAtDirection, m_cameraUpVector);
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

		//DEVI_INFO(std::to_string(m_cameraPosition.z), __FILE__, __LINE__);
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

		glm::vec3 lookAtVec(1.0);

		lookAtVec.x = cos(glm::radians(m_yawAngle)) * cos(glm::radians(m_pitchAngle));
		lookAtVec.y = sin(glm::radians(m_pitchAngle));
		lookAtVec.z = sin(glm::radians(m_yawAngle)) * cos(glm::radians(m_pitchAngle));
		m_cameraLookAtDirection = glm::normalize(lookAtVec);

		m_cameraRightVector = glm::cross(m_cameraLookAtDirection, GLOBAL_UP_VECTOR);
		m_cameraUpVector = glm::cross(m_cameraRightVector, m_cameraLookAtDirection);

		m_lastMousePos = currentMousePos;	
	}

}