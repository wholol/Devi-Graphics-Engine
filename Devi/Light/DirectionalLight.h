#pragma once
#include "Light.h"

namespace Devi
{
	class DirectionalLight : public Light

	{
	public:

		DirectionalLight(glm::vec3 LightDirection, glm::vec3 LightPosition, glm::vec3 m_LightColor = glm::vec3(1.0, 1.0, 1.0));
		glm::vec3 GetLightDirection() const;
		glm::vec3 GetLightPosition() const;

	private:
		glm::vec3 m_lightDirection;
		glm::vec3 m_lightPosition;	//technically directional light's position should be infinite, but for shadow mapping we need it for ortho matrix.		
	};
}
