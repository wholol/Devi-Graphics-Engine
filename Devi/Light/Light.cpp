#include "Light.h"

namespace Devi
{
	DirectionalLight::DirectionalLight(glm::vec3 lightDirection, glm::vec3 lightColor)
		:m_LightDirection(lightDirection),
		 m_LightColor(lightColor)
	{}

	glm::vec3 DirectionalLight::GetLightDirection() const
	{
		return m_LightDirection;
	}

	glm::vec3 DirectionalLight::GetLightColour() const
	{
		return m_LightColor;
	}
}

