#pragma once
#include "Math/glm/vec3.hpp"
#include "Math/glm/glm.hpp"
#include "Math/glm/gtc/matrix_transform.hpp"

static constexpr glm::vec3 GLOBAL_UP_VECTOR(0.0, 1.0, 0.0);
static constexpr float CAMERA_VELOCITY = 1.0f;

namespace Devi
{
	class Camera
	{

	public:
		//do note that the targetposition is not a direction only vector, it should be a coordiante as well ideally.
		Camera( glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f) , glm::vec3 cameraTargetPosition = glm::vec3(0.0,0.0,-1.0) );
		void Update(double deltaTime);
		glm::mat4 getViewMatrix() const;

	private:

		//translates the camera. note: direction vectors should be constant here.
		void translateCamera(double deltaTime);
		//rotates the camera around its position. note: direction vectors should be changed here.
		void rotateCamera(double deltaTime);

		//TODO
		void IncreaseCameraSpeed();
		//TODO
		void DecreaseCameraSpeed();


		glm::vec3 m_cameraPosition;
		glm::vec3 m_cameraTargetPosition;
		
		//camera axis vectors
		glm::vec3 m_cameraLookAtDirection;
		glm::vec3 m_cameraUpVector;
		glm::vec3 m_cameraRightVector;
	};

}