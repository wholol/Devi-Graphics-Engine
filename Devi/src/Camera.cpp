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

		//UpdateCameraVectors();
	}

	void Camera::Update(double deltaTime)
	{	
		//UpdateCameraVectors();
		translateCamera(deltaTime);
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
			m_cameraPosition -= CAMERA_VELOCITY * m_cameraRightVector;
		}

		else if (Inputs::IsKeyPressed(DeviKey::Key::D))
		{
			m_cameraPosition += CAMERA_VELOCITY * m_cameraRightVector;
		}
	}

	void Camera::UpdateCameraVectors()
	{
		auto currentMousePos = Devi::Inputs::GetMousePosInWindow();

		if (m_isFirstMouse)
		{
			m_lastMousePos = currentMousePos;
			m_isFirstMouse = false;
		}

		auto deltaMousePos = currentMousePos - m_lastMousePos;

		//update pitch yaw logic here.
		m_pitchAngle -= deltaMousePos.y * PITCH_SENSITVITY;

		m_yawAngle += deltaMousePos.x * YAW_SENSITIVITY;

		if (m_pitchAngle > 89.0)
		{
			m_pitchAngle = 89.0;
		}

		if (m_pitchAngle < -89.0)
		{
			m_pitchAngle = -89.0;
		}

		glm::vec3 lookAtVec;

		lookAtVec.x = cos(glm::radians(m_yawAngle)) * cos(glm::radians(m_pitchAngle));
		lookAtVec.y = sin(glm::radians(m_pitchAngle));
		lookAtVec.z = sin(glm::radians(m_yawAngle)) * cos(glm::radians(m_pitchAngle));
		m_cameraLookAtDirection = glm::normalize(lookAtVec);

		m_cameraRightVector = glm::cross(GLOBAL_UP_VECTOR, m_cameraLookAtDirection);
		m_cameraUpVector = glm::cross(m_cameraLookAtDirection, m_cameraUpVector);

		m_lastMousePos = currentMousePos;	
	}

}