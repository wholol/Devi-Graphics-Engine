#pragma once
#include "Math/glm/vec3.hpp"
#include "Math/glm/glm.hpp"
#include "Math/glm/gtc/matrix_transform.hpp"

static constexpr glm::vec3 GLOBAL_UP_VECTOR(0.0, 1.0, 0.0);
static constexpr float CAMERA_VELOCITY = 3.0f;
static constexpr double YAW_SENSITIVITY = 0.2;
static constexpr double PITCH_SENSITVITY = 0.2;

namespace Devi
{

	class Camera
	{

	public:
		//do note that the targetposition is not a direction only vector, it should be a coordiante as well ideally.
		Camera( glm::vec3 cameraPosition = glm::vec3(0.0f, 500.0f, 200.0f) , glm::vec3 cameraTargetPosition = glm::vec3(0.0,-0.67,-0.99) );
		void Update(double deltaTime);
		glm::mat4 getViewMatrix() const;

	private:

		//translates the camera. note: direction vectors should be constant here.
		void translateCamera(double deltaTime);
		//rotates the camera around its position. note: direction vectors should be changed here.
		void UpdateCameraVectors();

		glm::vec3 m_cameraPosition;
		glm::vec3 m_cameraTargetPosition;
		
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