#pragma once
#include <../Dependencies/Math/glm/glm.hpp>

namespace Devi
{
	class DirectionalLight
	{
	public:
		DirectionalLight(glm::vec3 lightDirection = glm::vec3(0.0, -1.0 ,0.0), glm::vec3 lightColor = glm::vec3(1.0,1.0,1.0));
		glm::vec3 GetLightDirection() const;
		glm::vec3 GetLightColour() const;

	private:
		glm::vec3 m_LightDirection;
		glm::vec3 m_LightColor;
	};
}
