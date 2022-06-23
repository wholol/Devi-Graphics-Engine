#pragma once
#include "Math/glm/vec3.hpp"
#include "Math/glm/glm.hpp"
#include "Math/glm/gtc/matrix_transform.hpp"

static constexpr glm::vec3 GLOBAL_UP_VECTOR(0.0, 1.0, 0.0);
static constexpr float CAMERA_VELOCITY = 500.0f;
static constexpr double YAW_SENSITIVITY = 40.0;
static constexpr double PITCH_SENSITVITY = 40.0;

namespace Devi
{
	class Camera
	{

	public:
		Camera();		
		void SetPosition(glm::vec3 position);
		void Update(double deltaTime);
		const glm::mat4& GetViewMatrix() const;
		const glm::mat4& GetWaterReflectionViewMatrix() const;
		glm::vec3 GetCameraPosition() const;

	private:

		//translates the camera. note: direction vectors should be constant here.
		void TranslateCamera(double deltaTime);
		//rotates the camera around its position. note: direction vectors should be changed here.
		void UpdateCameraVectors(double deltaTime);

		glm::vec3 m_cameraPosition;
		
		//camera axis vectors
		glm::vec3 m_cameraLookAtDirection;
		glm::vec3 m_cameraUpVector;
		glm::vec3 m_cameraRightVector;

		glm::highp_dvec2 m_lastMousePos;
		bool m_isFirstMouse = true;
		double m_pitchAngle = 0.0;
		double m_yawAngle = -90.0;
	};

}